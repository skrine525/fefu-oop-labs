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

class LivingRoom : public Room
{
public:
    LivingRoom() {}
    LivingRoom(int number, bool hasInternet, bool hasHotWater, bool hasGas, bool hasHeating);

    std::string getInfo(bool full = false, std::string tab = "") override;

private:
    bool hasInternet;
    bool hasHotWater;
    bool hasGas;
    bool hasHeating;
};

class ProductionRoom : public Room
{
public:
    ProductionRoom() {}
    ProductionRoom(int number, std::string label, unsigned machineCount, unsigned powerPerMachine);

    std::string getInfo(bool full = false, std::string tab = "") override;
    virtual void Produce();
private:
    std::string label;
    unsigned machineCount;
    unsigned powerPerMachine;
    unsigned goodsProducedCount;
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

class LivingBuilding : public Building
{
public:
    LivingBuilding() {}
    LivingBuilding(std::string street, bool hasParking, bool hasKindergartenNearby, bool hasSchoolNearby);
    ~LivingBuilding();

    std::string getInfo(bool full = false, std::string tab = "") override;

private:
    bool hasParking;
    bool hasKindergartenNearby;
    bool hasSchoolNearby;
};

class ProductionBuilding : public Building
{
public:
    ProductionBuilding() {}
    ProductionBuilding(std::string street, std::string name);
    ~ProductionBuilding();

    std::string getInfo(bool full = false, std::string tab = "") override;

private:
    std::string name;
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

    friend bool operator>(const City& a, const City& b);
    friend bool operator<(const City& a, const City& b);
    friend bool operator==(const City& a, const City& b);
    friend bool operator!=(const City& a, const City& b);
    friend bool operator>=(const City& a, const City& b);
    friend bool operator<=(const City& a, const City& b);

protected:
    std::string name;
    Container<Building>* buildings;
};

class CityManager
{
public:
    static CityManager& getInstance();

    City* createCity(std::string name);
    void printInfo();

private:
    static CityManager* p_instance;
    Container<City> cities;

    CityManager() {}
    CityManager(const CityManager&);
    CityManager& operator=(CityManager&);
};