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




// LIVE MUSIC START

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
        this->seated = true;
        this->standed = false;
    }
    else
    {
        this->seated = false;
        this->standed = true;
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
        result += "\n\n==Live Music==\n name:";
        result += iterator_->name;
        iterator_ = iterator_->next;
    }
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

    result+= "standed live music \n";
    
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
    result += " ";
    if(this->standed)
    {
        result += "s";
    }
    else
    {
        result += "S";
    }
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
        ticket_result += " ";
        ticket_result += iterator_->seat_number;
        
        ticket_file_out << ticket_result << endl;

        iterator_ = iterator_->next;
    }
}
// LIVE MUSIC END


// STANDUP START
class StandUpComedy : protected Event
{
public:

    StandUpComedy(string, char);

    string get_name()
    {
        return this->name;
    }

    void add_ticket(string, string, char, int);

    bool remove_ticket(string);

    string list_all(StandUpComedy *);

    string get_details();

    bool is_available();

    int tickets_count();

    void save();

    StandUpComedy *next = NULL;
    Ticket *ticket_head, *ticket_tail;
};


StandUpComedy::StandUpComedy(string name, char allocation)
{

    this->name = name;

    if(allocation=='S')
    {
        this->standed = false;
        this->seated = true;
    }
    else
    {
        throw invalid_argument("Got standed event while stand up comedy is only seated");
    }
    

}

void StandUpComedy::add_ticket(string reservee_name, string event_name, char event_type, int seat_number)
{
    Ticket *iterator_ = this->ticket_head;

    while(iterator_ != NULL)
    {   
        if(seat_number==0){
            iterator_->seat_number = 0;
        }
        else if(iterator_->seat_number == seat_number)
        {
            throw invalid_argument("The seat which you want is booked before");
        }
        iterator_ = iterator_->next;
    }

    Ticket *ticket_instance = new Ticket(reservee_name, event_name, event_type, seat_number);

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

bool StandUpComedy::remove_ticket(string reservee_name)
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

string StandUpComedy::list_all(StandUpComedy *head)
{
    string result = "";
    StandUpComedy *iterator_ = head;

    while(iterator_ != NULL)
    {
        result += "\n\n===Stand up===\n name:";
        result += iterator_->name;
        iterator_ = iterator_->next;
    }
    return result;
}

string StandUpComedy::get_details()
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
    result+= " seated \n";
    
    result+="reservations: ";
    
    Ticket *iterator_ = this->ticket_head;

    while(iterator_!=NULL)
    {
        result += iterator_->details();
        iterator_ = iterator_->next;
    }

    return result;
}

int StandUpComedy::tickets_count()
{
    Ticket *iterator_ = this->ticket_head;

    int counter = 0;
    
    while(iterator_ != NULL)
    {
        if(this->ticket_head==NULL)
        {
            break;
        }
        counter++;
        iterator_ = iterator_->next;
    }

    return counter;
}

bool StandUpComedy::is_available()
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

void StandUpComedy::save()
{
    string filename("events_data.txt");
    ofstream file_out;
    string result;

    file_out.open(filename, std::ios_base::app);
    result += "S ";
    result += this->name;
    result += " ";
    result += "S";
    file_out << result << endl;

    Ticket *iterator_ = ticket_head;
    
    while(iterator_!=NULL)
    {
        string ticket_filename("ticket_data.txt");
        ofstream ticket_file_out;
        string ticket_result;

        ticket_file_out.open(ticket_filename, std::ios_base::app);
        ticket_result += "S ";
        ticket_result += iterator_->reservee_name;
        ticket_result += " ";
        ticket_result += this->name;
        ticket_result += " ";
        ticket_result += to_string(iterator_->seat_number);
        ticket_file_out << ticket_result << endl;

        iterator_ = iterator_->next;
    }
}
// STANDUP END

// FILM START
class Film : protected Event
{
protected:
    int dimension;

public:

    Film(string, char, int);

    string get_name()
    {
        return this->name;
    }

    void add_ticket(string, string, char, int);

    bool remove_ticket(string);

    string list_all(Film *);

    string get_details();

    bool is_available();

    int tickets_count();

    void save();

    Film *next = NULL;
    Ticket *ticket_head, *ticket_tail;
};


Film::Film(string name, char allocation, int dimension)
{

    this->name = name;

    if(allocation=='S')
    {
        this->standed = false;
        this->seated = true;
    }
    else
    {
        throw invalid_argument("Got standed event while stand up comedy is only seated");
    }
    
    this->dimension = dimension;
}

void Film::add_ticket(string reservee_name, string event_name, char event_type, int seat_number)
{
    Ticket *iterator_ = this->ticket_head;

    while(iterator_ != NULL)
    {   
        if(seat_number==0){
            iterator_->seat_number = 0;
        }
        else if(iterator_->seat_number == seat_number)
        {
            throw invalid_argument("The seat which you want is booked before");
        }
        iterator_ = iterator_->next;
    }

    Ticket *ticket_instance = new Ticket(reservee_name, event_name, event_type, seat_number);

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

bool Film::remove_ticket(string reservee_name)
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

string Film::list_all(Film *head)
{
    string result = "";
    Film *iterator_ = head;

    while(iterator_ != NULL)
    {
        result += "\n\n===Stand up===\n name:";
        result += iterator_->name;
        iterator_ = iterator_->next;
    }
    return result;
}

string Film::get_details()
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
    result+= " seated \n";

    result+="dimension:";
    result+= to_string(this->dimension)+"D\n";
    
    result+="reservations: ";

    
    Ticket *iterator_ = this->ticket_head;

    while(iterator_!=NULL)
    {
        result += iterator_->details();
        iterator_ = iterator_->next;
    }

    return result;
}

int Film::tickets_count()
{
    Ticket *iterator_ = this->ticket_head;

    int counter = 0;
    
    while(iterator_ != NULL)
    {
        if(this->ticket_head==NULL)
        {
            break;
        }
        counter++;
        iterator_ = iterator_->next;
    }

    return counter;
}

bool Film::is_available()
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

void Film::save()
{
    string filename("events_data.txt");
    ofstream file_out;
    string result;

    file_out.open(filename, std::ios_base::app);
    result += "S ";
    result += this->name;
    result += " ";
    result += "S";
    file_out << result << endl;

    Ticket *iterator_ = ticket_head;
    
    while(iterator_!=NULL)
    {
        string ticket_filename("ticket_data.txt");
        ofstream ticket_file_out;
        string ticket_result;

        ticket_file_out.open(ticket_filename, std::ios_base::app);
        ticket_result += "S ";
        ticket_result += iterator_->reservee_name;
        ticket_result += " ";
        ticket_result += this->name;
        ticket_result += " ";
        ticket_result += to_string(iterator_->seat_number);
        ticket_file_out << ticket_result << endl;

        iterator_ = iterator_->next;
    }
}
// FILM END