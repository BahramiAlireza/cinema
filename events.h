#include <iostream>

using namespace std;

class Event
{
protected:
    bool standed, seated, allocated;
    const int seated_capacity = 200;
    const int standed_capacity = 300;
    int year, month, day;
    string name;

};


class LiveMusic : protected Event
{
private:
    int tracking_code;

public:
    LiveMusic(string name, int year, int month, int day, int tracking_code);
    string get_name(){ return this->name;}
LiveMusic *next;

};


LiveMusic::LiveMusic(string name, int year, int month, int day, int tracking_code)
{
    // STATIC PROPERTIES
    this->standed = true;
    this->seated = false;
    this->allocated = false;

    // SETTABLE PROPERTIES
    this->name = name;
    this->year = year;
    this->month = month;
    this->day = day;
    this->tracking_code = tracking_code;

}


class StandUpComedy : protected Event
{
private:
    int tracking_code;

public:
    StandUpComedy();

StandUpComedy *next;

};


StandUpComedy::StandUpComedy(/* args */)
{
    this->standed = true;
    this->seated = true;
    this->allocated = true;
}



class Film : protected Event
{
private:
    bool is_3d;
    int tracking_code;

public:
    Film();

Film *next;

};


Film::Film(/* args */)
{
    this->standed = true;
    this->seated = true;
    this->allocated = false;
}