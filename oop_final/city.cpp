#include "city.h"

bool operator>(const Room& a, const Room& b)
{
    return (a.number > b.number);
}

bool operator<(const Room& a, const Room& b)
{
    return (a.number < b.number);
}

bool operator==(const Room& a, const Room& b)
{
    return (a.number == b.number);
}

bool operator!=(const Room& a, const Room& b)
{
    return (a.number != b.number);
}

bool operator>=(const Room& a, const Room& b)
{
    return (a.number >= b.number);
}

bool operator<=(const Room& a, const Room& b)
{
    return (a.number <= b.number);
}

Room::Room(int number)
{
    this->number = number;
}

void Room::setBuilding(Building* building)
{
    this->building = building;
}

std::string Room::getAddress(bool full)
{
    if (full)
        return building->getAddress(full) + ", " + std::to_string(number);
    else
        return std::to_string(number);
}

std::string Room::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[Помещение]\n";
    info += tab + "Адрес: " + getAddress(true) + "\n";
    info += "\n";
    return info;
}

bool operator>(const Building& a, const Building& b)
{
    return (a.street > b.street);
}

bool operator<(const Building& a, const Building& b)
{
    return (a.street < b.street);
}

bool operator==(const Building& a, const Building& b)
{
    return (a.street == b.street);
}

bool operator!=(const Building& a, const Building& b)
{
    return (a.street != b.street);
}

bool operator>=(const Building& a, const Building& b)
{
    return (a.street >= b.street);
}

bool operator<=(const Building& a, const Building& b)
{
    return (a.street <= b.street);
}

Building::Building(std::string street)
{
    this->street = street;
    this->rooms = new Container<Room>;
    t = 1;
}

Building::~Building()
{
    if (rooms)
    {
        delete rooms;
        rooms = nullptr;
        t = 100;
    }
}

std::string Building::getAddress(bool full)
{
    if (full)
        return city->getName() + ", " + street;
    else
        return street;
}

std::string Building::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[Здание]\n";
    info += tab + "Адрес: " + getAddress(true) + "\n";
    if (full)
    {
        info += tab + "Помещения:\n";
        Container<Room>::Iterator beg = rooms->begin();
        Container<Room>::Iterator end = rooms->end();
        while (beg != end)
        {
            info += beg->getInfo(full, tab + "\t");
            beg++;
        }
    }
    info += "\n";
    return info;
}

void Building::setCity(City* city)
{
    this->city = city;
}

void Building::addRoom(Room* room)
{
    room->setBuilding(this);
    rooms->insertNode(room);
}

void Building::setRooms(Container<Room>* rooms)
{
    delete this->rooms;
    this->rooms = rooms;
    
    auto beg = this->rooms->begin();
    auto end = this->rooms->end();
    while (beg != end)
    {
        beg->setBuilding(this);
        beg++;
    }
}

City::City(std::string name)
{
    this->name = name;
    this->buildings = new Container<Building>;
}

City::~City()
{
    if (buildings)
    {
        delete buildings;
        buildings = nullptr;
    }
}

std::string City::getName()
{
    return name;
}

void City::addBuilding(Building* building)
{
    building->setCity(this);
    buildings->insertNode(building);
}

void City::setBuildings(Container<Building>* buildings)
{
    delete this->buildings;
    this->buildings = buildings;

    auto beg = this->buildings->begin();
    auto end = this->buildings->end();
    while (beg != end)
    {
        beg->setCity(this);
        beg++;
    }
}

std::string City::getInfo(bool full, std::string tab)
{
    std::string info;
    info = "Название города: " + name + "\n";

    if (full)
    {
        info += "Здания:\n";
        Container<Building>::Iterator beg = buildings->begin();
        Container<Building>::Iterator end = buildings->end();
        while (beg != end)
        {
            info += beg->getInfo(full, tab + "\t");
            beg++;
        }
    }

    return info;
}