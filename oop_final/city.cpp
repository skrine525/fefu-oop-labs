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
    info = tab + "[���������]\n";
    info += tab + "�����: " + getAddress(full) + "\n";
    info += "\n";
    return info;
}

LivingRoom::LivingRoom(int number, bool hasInternet, bool hasHotWater, bool hasGas, bool hasHeating) : Room(number)
{
    this->hasInternet = hasInternet;
    this->hasHotWater = hasHotWater;
    this->hasGas = hasGas;
    this->hasHeating = hasHeating;
}

std::string LivingRoom::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[����� ���������]\n";
    info += tab + "�����: " + getAddress(full) + "\n";
    info += tab + "��������: " + (hasInternet ? "����" : "���") + "\n";
    info += tab + "������� ����: " + (hasHotWater ? "����" : "���") + "\n";
    info += tab + "���: " + (hasGas ? "����" : "���") + "\n";
    info += tab + "���������: " + (hasHeating ? "����" : "���") + "\n";
    info += "\n";
    return info;
}

ProductionRoom::ProductionRoom(int number, std::string label, unsigned machineCount, unsigned powerPerMachine) : Room(number)
{
    this->label = label;
    this->machineCount = machineCount;
    this->powerPerMachine = powerPerMachine;
    this->goodsProducedCount = 0;
    this->produceCallback = nullptr;
}

ProductionRoom::~ProductionRoom()
{
    if (produceCallback)
        delete this->produceCallback;
}

std::string ProductionRoom::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[���������������� ���������]\n";
    info += tab + "�����: " + getAddress(full) + "\n";
    info += tab + "�����: " + label + "\n";
    info += tab + "���������� �������: " + std::to_string(machineCount) + "\n";
    info += tab + "�������� 1-�� ������: " + std::to_string(powerPerMachine) + "\n";
    info += tab + "����������� ����: " + std::to_string(goodsProducedCount) + "\n";
    info += "\n";
    return info;
}

void ProductionRoom::SetProduceCallback(std::function<void()> callback)
{
    if (this->produceCallback)
        delete this->produceCallback;
    this->produceCallback = new std::function<void()>(callback);
}

void ProductionRoom::Produce()
{
    this->goodsProducedCount += this->machineCount * this->powerPerMachine;
    if (this->produceCallback)
        (*this->produceCallback)();
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
    info = tab + "[������]\n";
    info += tab + "�����: " + getAddress(true) + "\n";
    if (full)
    {
        info += tab + "���������:\n";
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

LivingBuilding::LivingBuilding(std::string street, bool hasParking, bool hasKindergartenNearby, bool hasSchoolNearby) : Building(street)
{
    this->hasParking = hasParking;
    this->hasKindergartenNearby = hasKindergartenNearby;
    this->hasSchoolNearby = hasSchoolNearby;
}

LivingBuilding::~LivingBuilding()
{
    Building::~Building();
}

std::string LivingBuilding::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[����� ������]\n";
    info += tab + "�����: " + getAddress(true) + "\n";
    info += tab + "�������: " + (hasParking ? "����" : "���") + "\n";
    info += tab + "������� ��� �����: " + (hasKindergartenNearby ? "����" : "���") + "\n";
    info += tab + "����� �����: " + (hasSchoolNearby ? "����" : "���") + "\n";
    if (full)
    {
        info += tab + "���������:\n";
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

ProductionBuilding::ProductionBuilding(std::string street, std::string name) : Building(street)
{
    this->name = name;
}

ProductionBuilding::~ProductionBuilding()
{
    Building::~Building();
}

std::string ProductionBuilding::getInfo(bool full, std::string tab)
{
    std::string info;
    info = tab + "[���������������� ������]\n";
    info += tab + "�����: " + getAddress(true) + "\n";
    info += tab + "��������: " + name + "\n";
    if (full)
    {
        info += tab + "���������:\n";
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

bool operator>(const City& a, const City& b)
{
    return a.name > b.name;
}

bool operator<(const City& a, const City& b)
{
    return a.name < b.name;
}

bool operator==(const City& a, const City& b)
{
    return a.name == b.name;
}

bool operator!=(const City& a, const City& b)
{
    return a.name != b.name;
}

bool operator>=(const City& a, const City& b)
{
    return a.name >= b.name;
}

bool operator<=(const City& a, const City& b)
{
    return a.name <= b.name;
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
    info = "�������� ������: " + name + "\n";

    if (full)
    {
        info += "������:\n";
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

CityManager& CityManager::getInstance()
{
    if (!p_instance)
        p_instance = new CityManager();
    return *p_instance;
}

City* CityManager::createCity(std::string name)
{
    City* city = new City(name);
    cities.insertNode(city);
    return city;
}

void CityManager::printInfo()
{
    std::string info;
    auto beg = cities.begin();
    auto end = cities.end();
    while (beg != end)
    {
        info += beg->getInfo(true) + "\n";
        beg++;
    }
    std::cout << info;
}

CityManager* CityManager::p_instance = 0;