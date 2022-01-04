#include <iostream>
#include <stdexcept>

using namespace std;

char event_type_validator(char event_type)
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

    if(validated==true)
    {
        return event_type;
    }
    
    throw invalid_argument("Got invalid event type");
}