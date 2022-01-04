#include <iostream>
using namespace std;


class Ticket
{
    

public:
    int tracking_code;
    string event_name, reservee_name;
    char event_type;

    Ticket(string, string, char);

    Ticket *next = NULL;
};

Ticket::Ticket(string reservee_name, string event_name, char event_type){
    this->reservee_name = reservee_name;
    this->event_name = event_name;
    this->event_type = event_type;
}