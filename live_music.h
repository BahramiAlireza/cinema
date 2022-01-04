#include <iostream>
#include<string>  
#include <fstream>

#include "ticket.h"
#include "events.h"

using namespace std;


class LiveMusic : protected Event
{
public:

    LiveMusic(string, char);

    string get_name()
    {
        return this->name;
    }

    void add_ticket(string, string, char);

    bool remove_ticket(string);

    string list_all(LiveMusic *);

    string get_details();

    bool is_available();

    int tickets_count();

    void save();

    LiveMusic *next = NULL;
    Ticket *ticket_head, *ticket_tail;
};


LiveMusic::LiveMusic(string name, char allocation)
{

    // STATIC PROPERTIES
    this->allocated = false;

    // SETTABLE PROPERTIES
    this->name = name;

    if(allocation=='S')
    {
        this->standed = true;
        this->seated = false;
    }

}

void LiveMusic::add_ticket(string reservee_name, string event_name, char event_type)
{
    Ticket *ticket_instance = new Ticket(reservee_name, event_name, event_type);
    if(this->ticket_head==NULL)
    {
        this->ticket_head = ticket_instance;
        this->ticket_tail = ticket_head;
    }
    else
    {
        this->ticket_tail->next = ticket_instance;
        this->ticket_tail = ticket_instance;
    }
}

bool LiveMusic::remove_ticket(string reservee_name)
{
    Ticket *iterator_ = this->ticket_head;
    Ticket *previous_ticket = NULL;

    while(iterator_ != NULL)
    {
        if(iterator_->reservee_name == reservee_name)
        {
            if(previous_ticket != NULL)
            {
                previous_ticket->next = iterator_->next;
                delete iterator_;
                return true;
            }
            else
            {
                this->ticket_head = iterator_->next;
                delete iterator_;
                return true;
            }
            previous_ticket = iterator_;
            iterator_ = iterator_->next;
        }
    }
    return false;
}

string LiveMusic::list_all(LiveMusic *head)
{
    string result = "";
    LiveMusic *iterator_ = head;

    while(iterator_ != NULL)
    {
        result += "\n=============\n name:";
        result += iterator_->name;
        iterator_ = iterator_->next;
    }
    result += "\n=======\n";
    return result;
}

string LiveMusic::get_details()
{
    string result = "";
    result += "\n =========== \n name: ";
    result += this->name;
    result += "\n availability: ";
    if(this->is_available()==true)
    {
        result+= " available";
    }
    else
    {
        result+= " not_available";
    }
    result+= "\n type: ";
    if(this->seated)
    {
        result+= "seated live music \n";
    }
    else
    {
        result+= "standed live music \n";
    }
    
    return result;
}

int LiveMusic::tickets_count()
{
    Ticket *iterator_ = this->ticket_head;

    int counter = 0;
    
    while(iterator_ != NULL)
    {
        counter++;
        iterator_ = iterator_->next;
    }

    return counter;
}

bool LiveMusic::is_available()
{
    if(this->seated==true)
    {
        if(this->tickets_count() < this->seated_capacity)
            return true;
    }
    if(this->standed==true)
    {
        if(this->tickets_count() < this->standed_capacity)
            return true;
    }
    return false;
}

void LiveMusic::save()
{
    string filename("events_data.txt");
    ofstream file_out;
    string result;

    file_out.open(filename, std::ios_base::app);
    result += "L ";
    result += this->name;
    file_out << result << endl;

    Ticket *iterator_ = ticket_head;
    
    while(iterator_!=NULL)
    {
        string ticket_filename("ticket_data.txt");
        ofstream ticket_file_out;
        string ticket_result;

        ticket_file_out.open(ticket_filename, std::ios_base::app);
        ticket_result += "L ";
        ticket_result += iterator_->reservee_name;
        ticket_result += " ";
        ticket_result += this->name;
        ticket_file_out << ticket_result << endl;

        iterator_ = iterator_->next;
    }
}