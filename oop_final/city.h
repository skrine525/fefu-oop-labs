#pragma once
#include <string>
#include <iostream>
#include "container.h"

class City;
class Building;
class Room;

class Room
{
public:
    Room() {};
    Room(int number);

    virtual std::string getAddress(bool full = false);
    virtual std::string getInfo(bool full = false, std::string tab = "");

    friend bool operator>(const Room& a, const Room& b);
    friend bool operator<(const Room& a, const Room& b);
    friend bool operator==(const Room& a, const Room& b);
    friend bool operator!=(const Room& a, const Room& b);
    friend bool operator>=(const Room& a, const Room& b);
    friend bool operator<=(const Room& a, const Room& b);

    friend class Building;

protected:
    virtual void setBuilding(Building* building);

    int number;
    Building* building;
};

class Building
{
public:
    Building() {};
    Building(std::string street);
    ~Building();

    virtual void addRoom(Room* room);
    virtual void setRooms(Container<Room>* rooms);
    virtual std::string getAddress(bool full = false);
    virtual std::string getInfo(bool full = false, std::string tab = "");

    friend bool operator>(const Building& a, const Building& b);
    friend bool operator<(const Building& a, const Building& b);
    friend bool operator==(const Building& a, const Building& b);
    friend bool operator!=(const Building& a, const Building& b);
    friend bool operator>=(const Building& a, const Building& b);
    friend bool operator<=(const Building& a, const Building& b);

    friend class City;

protected:
    void setCity(City* city);

    int t;
    std::string street;
    City* city;
    Container<Room>* rooms;
};

class City
{
public:
    City(std::string name);
    ~City();

    virtual std::string getName();
    virtual void addBuilding(Building* building);
    virtual void setBuildings(Container<Building>* buildings);
    virtual std::string getInfo(bool full = false, std::string tab = "");

protected:
    std::string name;
    Container<Building>* buildings;
};