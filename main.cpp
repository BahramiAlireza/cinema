#include <iostream>
#include "events.h"

using namespace std;


LiveMusic *live_music_head = NULL;
LiveMusic *live_music_tail = NULL;


void remove_data(string file_name)
{
    ofstream ofs;
    ofs.open(file_name, ofstream::out | ofstream::trunc);
    ofs.close();
}

void save_data()
{
    remove_data("events_data.txt");
    remove_data("ticket_data.txt");

    LiveMusic *iterator_ = live_music_head;
    
    while(iterator_ != NULL)
    {
        iterator_->save();
        iterator_ = iterator_->next;
    }
}

void read_events_data()
{
    ifstream infile("events_data.txt");
    char event_type;
    string event_name;
    while (infile >> event_type >> event_name)
    {
        LiveMusic *obj = new LiveMusic(event_name);
        if(event_type=='L')
        {
            if(live_music_head==NULL)
            {
                live_music_head = obj;
                live_music_tail = live_music_head;
                cout<< live_music_head->get_name();
            }
            else
            {
                live_music_tail->next = obj;
                live_music_tail = obj;
            }
        } 
    }
}

void read_tickets_data()
{
    ifstream infile("ticket_data.txt");
    char event_type;
    string reservee_name, event_name;

    while(infile >> event_type >> reservee_name >> event_name)
    {
        if(event_type=='L')
        {
            LiveMusic *iterator_ = live_music_head;

            bool found = false;

            while(iterator_!=NULL)
            {
                if(iterator_->get_name()==event_name)
                {
                    iterator_->add_ticket(reservee_name, event_name, event_type);
                    found = true;
                }
                iterator_ = iterator_->next;
            }

            if(found == false)
            {
                cout << "No matching events found!\n";
            }
        }
    }
}

void get_details(char &command)
{
    string event_name;
    char event_type;
    LiveMusic *iterator_ = live_music_head;

    cout << "Enter name of event";
    cin >> event_name;

    cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
    cin >> event_type;

    while(iterator_ != NULL)
    {
        if(iterator_->get_name() == event_name)
        {
            cout << iterator_->get_details();
            cout << "!---press enter to continue---!";
            cin.ignore();
            cin.get();  
            return;
        }
        iterator_ = iterator_->next;
    }
    cout << "No matching event found!";
}

void book_event(char event_type, char& command)
{
    string event_name, reservee_name;

    LiveMusic *iterator_ = live_music_head;

    cout << "Enter the following:\n"\
            "Name of reservee: ";
    cin >> reservee_name;

    cout << "Event name:";
    cin >> event_name;

    while(iterator_!=NULL)
    {
        if(iterator_->get_name()==event_name)
        {

            iterator_->add_ticket(reservee_name, event_name, event_type);
            cout << "E: exit | B: book another event => ";
            cin >> command;
            return;
        }
        iterator_ = iterator_->next;
    }
    if(iterator_ == NULL)
    {
        cout << "No matching events found!\n";
    }

    cout << "E: exit | B: book another event => ";
    cin>>command;
    
}

void create_live_music(char &command)
{
    string name;

    cout << "Enter the following: \n"\
            "Event name: ";
    cin >> name;

    LiveMusic *obj = new LiveMusic(name);

    if(live_music_head==NULL)
    {
        live_music_head = obj;
        live_music_tail = live_music_head;
        cout<< live_music_head->get_name();
    }
    else
    {
        live_music_tail->next = obj;
        live_music_tail = obj;
    }
    cout << "E: exit | C: create another event => ";
    cin>>command;
}

void cancel_book(char &command)
{
    string event_name, reservee_name;
    char event_type;

    cout << "Enter the name of event: ";
    cin >> event_name;

    cout << "Enter the reservee name: ";
    cin >> reservee_name;

    cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
    cin >> event_type;




    LiveMusic *iterator_ = live_music_head;



    while(iterator_!=NULL)
    {

        if(iterator_->get_name()==event_name)
        {
            cout << iterator_->get_name() << "====" << event_name;
            if (iterator_->remove_ticket(reservee_name))
            {
                cout << "Object deleted!\n";
                cout << "E: exit | B: book another event => ";
                cin>>command;  
                return;
            }
            else
            {
                cout << "The booking object not found!\n";
                cout << "E: exit | B: book another event => ";
                cin>>command;  
                return;
            }
        }
        iterator_ = iterator_->next;
    }
    
    if(iterator_ == NULL)
    {
        cout << "No matching events found!\n";
    }

    cout << "E: exit | C: cancel another book => ";
    cin>>command;  
}


// CLI CONTROLLER
void cli(){
    char command, event_type;
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
                // .......
            }
            command = ' ';
        }
        else if (command ==  'a')
        {
            while(command != 'E')
            {
                cout << "Enter type of event you are going to add a booking -> \n L: live music | S: stand up comedy | F: film | E: exit => ";
                cin>>event_type;

                while(command!='E')
                    book_event(event_type, command);

            }
            command = ' ';
        }
        else if (command == 'C')
        {
            while(command != 'E')
            {
                cancel_book(command);
            }
        }

        else if (command == 'L')
        {
            if(live_music_head != NULL){
                cout<<live_music_head->list_all(live_music_head);
                cout << "!---press enter to continue---!";
                cin.ignore();
                cin.get();  
            }
            else
            {
                cout << "No Live musics found";
            }  
        }
        else if (command == 'l')
        {
            get_details(command);
        }
        else if (command == 'D')
        {
            read_events_data();
            read_tickets_data();
        }
        else if (command == 'S')
        {
            save_data();
        }
        
    }
}

int main(){   
    cli();
    // Ticket *it = live_music_head->ticket_head;
    // while(it!=NULL){
    //     cout<<it->l();
    //     it=it->live_music_head->nex;
    // }
}