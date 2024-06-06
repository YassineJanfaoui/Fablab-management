#include "room.h"

room::room()
{

}

room::room(int id, const QString& type, int capacity, const QString& availibility)
    : IDRoom(id), TypeRoom(type), RoomCapacity(capacity), RoomAvailibility(availibility)
{

}

room::room(const room& other)
    : IDRoom(other.IDRoom), TypeRoom(other.TypeRoom), RoomCapacity(other.RoomCapacity),
      RoomAvailibility(other.RoomAvailibility)
{

}
