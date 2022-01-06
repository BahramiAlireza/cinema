#include <iostream>
#include <string>
#include "events.h"

using namespace std;


LiveMusic *live_music_head = NULL;
LiveMusic *live_music_tail = NULL;

StandUpComedy *stand_up_head = NULL;
StandUpComedy *stand_up_tail = NULL;

Film *film_head = NULL;
Film *film_tail = NULL;

// validators
bool event_type_validator(char event_type)
{
    bool validated = false;

    if(event_type=='L')
    {
     validated = true;   
    }
    else if (event_type=='S')
    {
     validated = true;   
    }
    else if (event_type=='F')
    {
     validated = true;   
    }

    return validated;
}

bool seat_number_validator(int seat_number)
{
    if(seat_number>=0 && seat_number<200)
    {
        return true;
    }
    
    return false;
}


// cli
void pause(string msg)
{
    cout << "\n" << msg;
    cout << "\npress any key to continue...\n";
    std::cin.ignore();
    std::cin.get(); 
}

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

    StandUpComedy *stand_up_iterator_ = stand_up_head;
    
    while(stand_up_iterator_ != NULL)
    {
        stand_up_iterator_->save();
        stand_up_iterator_ = stand_up_iterator_->next;
    }

    Film *film_iterator_ = film_head;
    
    while(film_iterator_ != NULL)
    {
        film_iterator_->save();
        film_iterator_ = film_iterator_->next;
    }
    pause("Data saved!");
}

void read_events_data()
{
    ifstream infile("events_data.txt");
    char event_type, allocation;
    string event_name, dimension_string;
    int dimension;



    while (infile >> event_type >> event_name >> allocation >> dimension_string)
    {
        
        while (event_type_validator(event_type) == false)
        {
            throw invalid_argument("wrong data (invalid event type found in data)");
        }

        dimension = stoi(dimension_string);

   
        if(event_type == 'L')
        {
            LiveMusic *obj = new LiveMusic(event_name, allocation);

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
        }
        else if (event_type=='S')
        {
            StandUpComedy *obj = new StandUpComedy(event_name, allocation);

            if(stand_up_head==NULL)
            {
                stand_up_head = obj;
                stand_up_tail = stand_up_head;
            }
            else
            {
                stand_up_tail->next = obj;
                stand_up_tail = obj;
            }
        }
        else if (event_type=='F')
        {
            if ( (dimension<=1 || dimension>3) || dimension==0)
            {
                throw invalid_argument("wrong data (invalid film dimension found in data)");
            }
        
            Film *obj = new Film(event_name, allocation, dimension);

            if(film_head==NULL)
            {
                film_head = obj;
                film_tail = film_head;
            }
            else
            {
                film_tail->next = obj;
                film_tail = obj;
            }
        }
    }
    pause("Events loaded successfully!\n");
}

void read_tickets_data()
{
    ifstream infile("ticket_data.txt");
    char event_type;
    string reservee_name, event_name, seat_number_string;
    int seat_number;

    while(infile >> event_type >> reservee_name >> event_name >> seat_number_string)
    {
        while (event_type_validator(event_type) == false)
        {
            throw invalid_argument("wrong data (invalid event type found in data)");
        }
        seat_number = stoi(seat_number_string);

        if(seat_number_validator(seat_number)==false)
        {
            throw invalid_argument("wrong data (invalid seat number in data)");
        }

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
        else if (event_type=='S')
        {
            StandUpComedy *iterator_ = stand_up_head;


            bool found = false;
            int seat_number = 0;

            while(iterator_!=NULL)
            {
                if(iterator_->get_name()==event_name)
                {
                    seat_number = stoi(seat_number_string);
                    iterator_->add_ticket(reservee_name, event_name, event_type, seat_number);
                    found = true;
                }
                iterator_ = iterator_->next;
            }

            if(found == false)
            {
                cout << "No matching events found!\n";
            }
        }
        else if (event_type=='F')
        {
            Film *iterator_ = film_head;


            bool found = false;
            int seat_number = 0;

            while(iterator_!=NULL)
            {
                if(iterator_->get_name()==event_name)
                {
                    seat_number = stoi(seat_number_string);
                    iterator_->add_ticket(reservee_name, event_name, event_type, seat_number);
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
    pause("Reservations loaded successfully!\n");
}

void get_details(char &command)
{
    string event_name;
    char event_type;

    cout << "Enter name of event: ";
    std::cin >> event_name;

    cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
    std::cin >> event_type;


    while(event_type_validator(event_type)==false)
    {
        cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
        std::cin >> event_type;
    }

    if(event_type=='L')
    {
        LiveMusic *iterator_ = live_music_head;

        while(iterator_ != NULL)
        {
            if(iterator_->get_name() == event_name)
            {
                cout << iterator_->get_details();
                pause("*********");
                return;
            }
            iterator_ = iterator_->next;
        }
    }
    else if(event_type=='S')
    {
        StandUpComedy *iterator_ = stand_up_head;

        while(iterator_ != NULL)
        {
            if(iterator_->get_name() == event_name)
            {
                cout << iterator_->get_details();
                pause("********");
                return;
            }
            iterator_ = iterator_->next;
        }
    }
    else if(event_type=='F')
    {
        Film *iterator_ = film_head;

        while(iterator_ != NULL)
        {
            if(iterator_->get_name() == event_name)
            {
                cout << iterator_->get_details();
                pause("********");
                return;
            }
            iterator_ = iterator_->next;
        }
    }

    cout << "No matching event found!";
}

void book_event(char event_type, char& command)
{
    string event_name, reservee_name;
    
    while(event_type_validator(event_type)==false)
    {
        cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
        std::cin >> event_type;
    }

    cout << "Enter the following:\n"\
            "Name of reservee: ";
    std::cin >> reservee_name;

    cout << "Event name:";
    std::cin >> event_name;

    if(event_type == 'L')
    {
        LiveMusic *iterator_ = live_music_head;

        while(iterator_!=NULL)
        {
            if(iterator_->get_name()==event_name)
            {
                if(iterator_->is_available()==true)
                {
                    iterator_->add_ticket(reservee_name, event_name, event_type);
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        if(iterator_ == NULL)
        {
            cout << "No availiable events found!\n";
        }
    }
    else if (event_type=='S')
    {
        StandUpComedy *iterator_ = stand_up_head;

        while(iterator_!=NULL)
        {
            if(iterator_->get_name()==event_name)
            {
                if(iterator_->is_available()==true)
                {
                    int seat_number = 0;

                    cout <<"Enter the seat number you want to book:";
                    std::cin >> seat_number;

                    iterator_->add_ticket(reservee_name, event_name, event_type, seat_number);
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        if(iterator_ == NULL)
        {
            cout << "No matching events found!\n";
        }
    }
    else if (command=='F')
    {
        Film *iterator_ = film_head;

        while(iterator_!=NULL)
        {
            if(iterator_->get_name()==event_name)
            {
                if(iterator_->is_available()==true)
                {
                    int seat_number = 0;

                    iterator_->add_ticket(reservee_name, event_name, event_type, seat_number);
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        if(iterator_ == NULL)
        {
            cout << "No matching events found!\n";
        }
    }
}

void create_event(char &command)
{

    string name;
    char allocation;

    cout << "Enter the following: \n"\
            "Event name: ";
    std::cin >> name;
    
    if(command=='L')
    {
        allocation = 's';

        LiveMusic *obj = new LiveMusic(name, allocation);

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
    }
    else if (command=='S')
    {
        allocation = 'S';
        StandUpComedy *obj = new StandUpComedy(name, allocation);
        if(stand_up_head==NULL)
        {
            stand_up_head = obj;
            stand_up_tail = stand_up_head;
        }
        else
        {
            stand_up_tail->next = obj;
            stand_up_tail = obj;
        }

    }
    else if(command == 'F')
    {
        int dimension;
        allocation = 'S';

        cout << "Enter 2: 2d film | 3: 3d film";
        std::cin >> dimension;

        Film *obj = new Film(name, allocation, dimension);

        if(film_head==NULL)
        {
            film_head = obj;
            film_tail = film_head;
        }
        else
        {
            film_tail->next = obj;
            film_tail = obj;
        }
    }
    

}

void cancel_book(char &command)
{
    string event_name, reservee_name;
    char event_type;

    cout << "Enter the name of event: ";
    std::cin >> event_name;

    cout << "Enter the reservee name: ";
    std::cin >> reservee_name;

    cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
    std::cin >> event_type;


    while(event_type_validator(event_type)==false)
    {
        cout << "Enter the type of event: L: live music | S: stand up comedy | F: film =>  ";
        std::cin >> event_type;
    }

    if (event_type=='L')
    {
        LiveMusic *iterator_ = live_music_head;

        while(iterator_!=NULL)
        {

            if(iterator_->get_name()==event_name)
            {
                cout << iterator_->get_name() << "====" << event_name;
                if (iterator_->remove_ticket(reservee_name))
                {
                    cout << "Object deleted!\n";
                    return;
                }
                else
                {
                    cout << "The booking object not found!\n";
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        
        if(iterator_ == NULL)
        {
            cout << "No matching events found!\n";
        }
    }
    else if (event_type == 'S')
    {
        LiveMusic *iterator_ = live_music_head;

        while(iterator_!=NULL)
        {

            if(iterator_->get_name()==event_name)
            {
                cout << iterator_->get_name() << "====" << event_name;
                if (iterator_->remove_ticket(reservee_name))
                {
                    cout << "Object deleted!\n";
                    return;
                }
                else
                {
                    cout << "The booking object not found!\n";
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        
        if(iterator_ == NULL)
        {
            cout << "No matching events found!\n";
        }
    }
    else if (event_type == 'F')
    {
        Film *iterator_ = film_head;

        while(iterator_!=NULL)
        {

            if(iterator_->get_name()==event_name)
            {
                cout << iterator_->get_name() << "====" << event_name;
                if (iterator_->remove_ticket(reservee_name))
                {
                    cout << "Object deleted!\n";
                    return;
                }
                else
                {
                    cout << "The booking object not found!\n";
                    return;
                }
            }
            iterator_ = iterator_->next;
        }
        
        if(iterator_ == NULL)
        {
            cout << "No matching events found!\n";
        }
    } 
}


// CLI CONTROLLER
void cli(){
    char command, event_type;
    while(command != 'E')
    {
        cout << "Menu -> \n A: add event \n a: add booking \n C: cancel booking"\
                "\n L: list all events \n l: get details of an event \n D: load data from file"\
                "\n S: save data to file \n E: exit.\n";

        std::cin>>command;

        if(command == 'A'){
                cout << "Enter type of event -> \n L: live music | S: stand up comedy | F: film | E: exit =>";
                std::cin>>command;
                
                create_event(command);

            command = ' ';
        }
        else if (command ==  'a')
        {
            cout << "Enter type of event you are going to add a booking -> \n L: live music | S: stand up comedy | F: film | E: exit => ";
            std::cin>>event_type;

            book_event(event_type, command);

            command = ' ';
        }
        else if (command == 'C')
        {
            cancel_book(command);
        }

        else if (command == 'L')
        {           
            if(live_music_head != NULL || stand_up_head != NULL ){
                cout<<live_music_head->list_all(live_music_head);
                cout<<stand_up_head->list_all(stand_up_head);
                cout<<film_head->list_all(film_head);
                pause("");
            }
            else
            {
                cout << "No events found\n";
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
}