#include "LeaveEvent.h"

LeaveEvent::LeaveEvent(int ID, Station* sStation, Time etime)
{
    st_station = sStation;
    event_time = etime;
    passenger_id = ID;
}

void LeaveEvent::Excute()
{
    st_station->remove_NP(passenger_id);
}

Time LeaveEvent::get_event_time()
{
    return event_time;
}
