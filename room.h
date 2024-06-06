#ifndef ROOM_H
#define ROOM_H
#include <QString>
#include <QDate>

class room
{
public:
    room();
    room(int id, const QString& type, int capacity, const QString& availibility);
    room(const room& other);

    int getIDRoom() const { return IDRoom; }
    QString getTypeRoom() const { return TypeRoom; }
    int getCapacity() const { return RoomCapacity; }
    QString getAvailibility() const { return RoomAvailibility; }

    void setIDRoom(int id) { IDRoom = id; }
    void setTypeRoom(const QString& type) { TypeRoom = type; }
    void setCapacity(int capacity) { RoomCapacity = capacity; }
    void setAvailibility(const QString& availibility) { RoomAvailibility = availibility; }


    private:
    int IDRoom;
    QString TypeRoom;
    int RoomCapacity;
    QString RoomAvailibility;
};

#endif // ROOM_H

