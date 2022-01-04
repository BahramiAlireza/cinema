#include <iostream>
#include<string>  
#include <fstream>

#include "ticket.h"

using namespace std;

class Event
{
protected:
    bool standed, seated, allocated;
    const int seated_capacity = 200;
    const int standed_capacity = 300;
    string name;

};


class LiveMusic : protected Event
{
public:

    LiveMusic(string);

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


    LiveMusic *next = NULL;
    Ticket *ticket_head, *ticket_tail;
};


LiveMusic::LiveMusic(string name)
{
    // STATIC PROPERTIES
    this->standed = true;
    this->seated = false;
    this->allocated = false;

    // SETTABLE PROPERTIES
    this->name = name;

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
        result+= "\n available";
    }
    else
    {
        result+= "\n not_available";
    }
    result+= "\n type: ";
    if(this->seated)
    {
        result+= "\n seated live music";
    }
    else
    {
        result+= "\n standed live music";
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

