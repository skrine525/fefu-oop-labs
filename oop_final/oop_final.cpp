#include <iostream>
#include "city.h"
#include "decorator.h"

/*
* Что встроено:
* Контейнер (двухсвязный кольцевой список без повторов, упорядоченный по возрастанию) + двунаправленный итератор
*/

int main()
{
    setlocale(LC_ALL, "Russian");

    // Демонстрация билдера
    ContainerBuilder<Room> roomBuilder;
    roomBuilder.add(new Room(10));
    roomBuilder.add(new Room(20));
    roomBuilder.add(new Room(30));

    Building* building1 = new Building("Уткинская");
    Building* building2 = new Building("Спортивная");
    building1->setRooms(roomBuilder.get());
    building2->setRooms(roomBuilder.get());

    // Демонстрация наследования Room и декоратора
    Building* building3 = new Building("Державина");
    building3->addRoom(new Room(10));
    building3->addRoom(new LivingRoom(20, true, false, true, false));
    building3->addRoom(new LivingRoom(30, false, true, false, true));
    ProductionRoom* productionRoom = new ProductionRoom(40, "Производство спичек", 10, 5);
    building3->addRoom(productionRoom);
    Decorator::ProduceDecorator produceDecorated(productionRoom, 5);    // Декоратор, который выполнит 5 раз Produce
    produceDecorated.Produce();                                         // Выполняем обернутый Produce

    // Демонстрация наследования Building
    ProductionBuilding* building4 = new ProductionBuilding("Русская", "Завод покрышек");
    building4->addRoom(new ProductionRoom(5, "Цех 1", 6, 2));
    building4->addRoom(new ProductionRoom(6, "Цех 2", 4, 2));
    building4->addRoom(new ProductionRoom(7, "Цех 3", 7, 2));
    LivingBuilding* building5 = new LivingBuilding("Светланская", true, false, true);
    building5->addRoom(new LivingRoom(120, true, true, false, true));
    building5->addRoom(new LivingRoom(125, true, true, true, true));
    building5->addRoom(new LivingRoom(130, false, false, false, false));
    building5->addRoom(new LivingRoom(135, true, false, true, true));

    // Синглтон
    City* vdk = CityManager::getInstance().createCity("Владивосток");
    vdk->addBuilding(building1);
    vdk->addBuilding(building2);
    vdk->addBuilding(building3);
    vdk->addBuilding(building4);
    vdk->addBuilding(building5);
    City* usr = CityManager::getInstance().createCity("Уссурийск");
    Building* building6 = new Building("Красного знамени");
    building6->setRooms(roomBuilder.get());
    usr->addBuilding(building6);
    CityManager::getInstance().printInfo();

    return 0;
}

