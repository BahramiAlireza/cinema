#include <iostream>

using namespace std;


class Event
{
protected:
    bool standed, seated, allocated;
    const int seated_capacity = 200;
    const int standed_capacity = 300;
    string name;
public:
    void read_data();
};