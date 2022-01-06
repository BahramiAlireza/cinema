#include <iostream>
using namespace std;


class Ticket
{
    

public:
    string event_name, reservee_name;
    char event_type;
    int seat_number;

    Ticket(string, string, char, int = 0);

    string details();

    Ticket *next = NULL;
};

Ticket::Ticket(string reservee_name, string event_name, char event_type, int seat_number){
    this->reservee_name = reservee_name;
    this->event_name = event_name;
    this->event_type = event_type;

    if(seat_number!=0)
    {
        this->seat_number = seat_number;
    }
}

string Ticket::details()
{
    string result = "";
    result += "\n********\n";
    result += "reservee name: ";
    result += this->reservee_name + "\n";
    if(this->seat_number!=0)
    {
        result+="seat number: ";
        result+= to_string(this->seat_number);
    }
    return result;
}