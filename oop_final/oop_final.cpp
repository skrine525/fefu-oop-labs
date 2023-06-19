#include <iostream>
#include "city.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    ContainerBuilder<Room> roomBuilder;
    roomBuilder.add(new Room(500));
    roomBuilder.add(new Room(501));
    roomBuilder.add(new Room(502));

    Building* building1 = new Building("Уткинская");
    Building* building2 = new Building("Матросова");
    building1->setRooms(roomBuilder.get());
    building2->setRooms(roomBuilder.get());

    City vdk("Владивосток");
    vdk.addBuilding(building1);
    vdk.addBuilding(building2);
    std::cout << vdk.getInfo(true) << std::endl;

    return 0;
}

