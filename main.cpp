#include <iostream>
#include "events.h"

using namespace std;


LiveMusic *live_music_head = NULL;
LiveMusic *live_music_tail = NULL;

void create_live_music(char &command)
{
    string name;
    int year, month, day, tracking_code;

    cout << "Enter the following: \n"\
            "Event name: ";
    cin >> name;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month: ";
    cin >> month;
    cout << "Enter day: ";
    cin >> day;
    cout << "Enter tracking_code: ";
    cin>> tracking_code;

    LiveMusic *obj = new LiveMusic(name, year, month, day, tracking_code);

    if(live_music_head==NULL)
    {
        live_music_head = obj;
        live_music_tail = live_music_head;
    }
    else
    {
        live_music_tail->next = obj;
        live_music_tail = obj;
    }

    cout << "E: exit | C: create another event => ";
    cin>>command;
}


// CLI CONTROLLER
void cli(){
    char command;
    while(command != 'E'){
        cout << "Menu -> \n A: add event \n a: add booking \n C: cancel booking"\
                "\n L: list all events \n l: get details of an event \n D: load data from file"\
                "\n S: save data to file \n E: exit.\n";

        cin>>command;

        if(command == 'A'){
            while(command != 'E')
            {
                cout << "Enter type of event -> \n L: live music | S: stand up comedy | F: film | E: exit =>";
                cin>>command;
                
                if(command=='L')
                {
                    while(command!='E')
                        create_live_music(command);
                }
            }
            command = ' ';
        }
    }
}

int main(){   
    cli();
    LiveMusic *it = live_music_head;
    while(it!=NULL){
        cout<<it->m_n();
        it=it->next;
    }
}