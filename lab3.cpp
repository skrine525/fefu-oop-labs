#include <iostream>
#include <chrono>
#include <cstring>
#include <fstream>
#include <regex>

const std::string FILEPATH = "notes.txt";

struct Note
{
    std::string name; // ФИО
    std::string tele; // телефон
    std::chrono::year_month_day birthday; //день рождения
};

void checkFile(std::string tele);
void writeFile(int noteCount, Note& note);


int main()
{
    std::string tele;
    std::cout << "Enter Tele: ";
    std::cin >> tele;

    if (std::regex_match(tele, std::regex("\\d+")) && tele.length() == 11)
        checkFile(tele);
    else
        std::cout << "Incorrect input!" << std::endl;

    return 0;   // А вот в визуалке это не надо
}

void checkFile(std::string tele)
{
    std::ifstream fin(FILEPATH, std::ios::in | std::ios::binary);
    int noteCount = 0;

    if (fin.is_open())
    {
        Note* data;
        fin.read((char*)&noteCount, sizeof(noteCount));

        Note* notes = new Note[noteCount];

        bool isFound = false;
        char* readByte = new char;
        for (int i = 0; i < noteCount; i++)
        {
            std::string readName;
            std::string readTele;
            std::chrono::year_month_day readBirthday;

            *readByte = 1;
            while (*readByte != 0)
            {
                fin.read(readByte, 1);
                if(*readByte != 0)
                    readName += *readByte;
            }

            *readByte = 1;
            while (*readByte != 0)
            {
                fin.read(readByte, 1);
                if (*readByte != 0)
                    readTele += *readByte;
            }

            fin.read((char*)&readBirthday, sizeof(readBirthday));

            notes[i].name = readName;
            notes[i].tele = readTele;
            notes[i].birthday = readBirthday;
        }
        delete readByte;


        for (int i = 0; (i < noteCount) && !isFound; i++)
        {
            if (notes[i].tele == tele)
            {
                std::cout << "Found!\nName: " << notes[i].name << "\nTele: " << notes[i].tele << "\nBirthday: " << notes[i].birthday << std::endl;
                isFound = true;
            }
        }
        delete[] notes;

        if (!isFound)
        {
            std::string name;
            int y, m, d;
            std::cout << "Not found! Let's add.\nEnter Name: ";
            std::cin >> name;
            std::cout << "Enter Birthday (YYYY MM DD): ";
            if (!(std::cin >> y >> m >> d))
                std::cout << "Incorrect input!" << std::endl;
            else
            {
                Note note;
                note.tele = tele;
                note.name = name;
                note.birthday = { std::chrono::day(d) / std::chrono::month(m) / std::chrono::year(y) };
                writeFile(noteCount, note);
            }
        }
    }
    else
    {
        std::string name;
        int y, m, d;
        std::cout << "Not found! Let's add.\nEnter Name: ";
        std::cin >> name;
        std::cout << "Enter Birthday (YYYY MM DD): ";
        if (!(std::cin >> y >> m >> d))
            std::cout << "Incorrect input!" << std::endl;
        else
        {
            Note note;
            note.tele = tele;
            note.name = name;
            note.birthday = { std::chrono::day(d) / std::chrono::month(m) / std::chrono::year(y) };
            writeFile(0, note);
        }
    }
    fin.close();
}

void writeFile(int noteCount, Note& note)
{
    std::ifstream fin(FILEPATH, std::ios::in);
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end);
        int bytes = fin.tellg();
        fin.seekg(4, std::ios::beg);
        char* readBytes = new char[bytes - 4];
        fin.read(readBytes, bytes - 4);
        fin.close();

        std::ofstream fout(FILEPATH, std::ios::out | std::ios::binary);
        noteCount++;
        fout.write((char*)&noteCount, sizeof(noteCount));
        fout.write(readBytes, bytes - 4);
        fout.write(note.name.c_str(), note.name.size() + 1);
        fout.write(note.tele.c_str(), note.tele.size() + 1);
        fout.write((char*)&note.birthday, sizeof(note.birthday));
        fout.close();
        delete[] readBytes;
    }
    else
    {
        std::ofstream fout(FILEPATH, std::ios::out | std::ios::binary);
        noteCount++;
        fout.write((char*)&noteCount, sizeof(noteCount));
        fout.write(note.name.c_str(), note.name.size() + 1);
        fout.write(note.tele.c_str(), note.tele.size() + 1);
        fout.write((char*)&note.birthday, sizeof(note.birthday));
        fout.close();
    }
}