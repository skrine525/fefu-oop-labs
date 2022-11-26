#include <string>
#include <iostream>
#include <windows.h>

struct Marsh
{
    std::string begst;
    std::string term;
    short numer;
};

int main()
{
    const int N = 2;

    Marsh traffic[N];

    // Вводим данные
    for (int i = 0; i < N; i++)
    {
        std::cout << "Traffic " << (i + 1) << std::endl << "Begst: ";
        std::getline(std::cin, traffic[i].begst);
        std::cout << "Term: ";
        std::getline(std::cin, traffic[i].term);
        std::cout << "Numer: ";
        std::cin >> traffic[i].numer;
        std::cout << std::endl;
        std::cin.ignore(INT_MAX, '\n'); // Без этого ничо не робит ¯\_(ツ)_/¯
    }

    // Сортируем данные
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (traffic[i].numer > traffic[j].numer)
            {
                Marsh tmp = traffic[i];
                traffic[i] = traffic[j];
                traffic[j] = tmp;
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        std::cout << traffic[i].numer << std::endl;
    }

    system("cls");

    bool active = true;
    std::string name;
    while (active)
    {
        std::cout << "Name (type exit to exit): ";
        std::cin.ignore(INT_MAX, '\n'); // Без этого ничо не робит ¯\_(ツ)_/¯
        std::cin >> name;
        if (name == "exit")
            active = false;
        else
        {
            bool printed = false;
            for (size_t i = 0; i < N; i++)
            {
                if (traffic[i].begst == name || traffic[i].term == name)
                {
                    std::cout << "Begst: " << traffic[i].begst << "\nTerm: " << traffic[i].term << "\nNumer: " << traffic[i].numer << "\n\n";
                    if (!printed)
                        printed = true;
                }
            }

            if (!printed)
                std::cout << "Not found" << std::endl;
            system("pause");
            system("cls");
        }
    }
}

