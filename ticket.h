# include "events.h"

class Ticket
{
private:
    int tracking_code, reservee_name, tracking_code, event_id, event_type;

public:
    Ticket(int reservee_name, int event_id, int event_type);

    Ticket *next;
};

Ticket::Ticket(int reservee_name, int event_id, int event_type){
    this->reservee_name = reservee_name;
    this->event_id = event_id;
    this->event_type = event_type;
}