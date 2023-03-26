#include <iostream>
#include <iterator>
#include <cstddef>
#include <string>

class Employee
{
protected:
    double salary;              // Зарплата
    unsigned exp;               // Опыт
    std::string profName;       // Название профессии
    std::string employeeName;   // Название профессии

public:
    Employee(std::string employeeName, double salary)
    {
        this->profName = "Работник";
        this->employeeName = employeeName;
        this->salary = salary;
        this->exp = 0;
    }

    void Work()
    {
        this->exp++;
        std::cout << this->profName << " " << this->employeeName << " выходит на смену.\n";
        std::cout << this->profName << " " << this->employeeName << " за смену заработал(а) $" << this->salary << ".\n";
    }

    // Операторы сравнения
    friend bool operator>(const Employee& a, const Employee& b) { return a.salary > b.salary || (a.salary == b.salary && a.exp > b.exp); }
    friend bool operator<(const Employee& a, const Employee& b) { return a.salary < b.salary || (a.salary == b.salary && a.exp < b.exp); }
    friend bool operator==(const Employee& a, const Employee& b) { return a.salary == b.salary && a.exp == b.exp; }
    friend bool operator!=(const Employee& a, const Employee& b) { return !(a == b); }
    friend bool operator>=(const Employee& a, const Employee& b) { return a > b || a == b; }
    friend bool operator<=(const Employee& a, const Employee& b) { return a < b || a == b; }
};

class Patient
{
public:
    std::string patientName;
    std::string report;
};

class Patients
{
public:
    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Patient;
        using pointer = Patient*;
        using reference = Patient&;

        Iterator() {}   // Нужен, потому что в конструкторе билдера ошибка: ГДЕ КОНСТРУКТОР ПО УМОЛЧАНИЮ????
        Iterator(Patients::Iterator& o) : m_ptr(o.m_ptr) {}
        Iterator(Patients::Iterator&& o) noexcept : m_ptr(std::move(o.m_ptr)) { o.m_ptr = nullptr; }
        Iterator(pointer ptr) : m_ptr(ptr) {}
        ~Iterator() {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { m_ptr--; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.m_ptr > b.m_ptr; };
        friend bool operator>= (const Iterator& a, const Iterator& b) { return (a.m_ptr > b.m_ptr) || (a.m_ptr == b.m_ptr); };
        friend bool operator<= (const Iterator& a, const Iterator& b) { return (a.m_ptr < b.m_ptr) || (a.m_ptr == b.m_ptr); };

        Iterator& operator+(int n) { m_ptr = m_ptr + n; return *this; }
        Iterator& operator-(int n) { m_ptr = m_ptr - n; return *this; }
        Iterator& operator+=(int n) { m_ptr = m_ptr + n; return *this; }
        Iterator& operator-=(int n) { m_ptr = m_ptr - n; return *this; }


        // copy assignment
        Iterator& operator=(const Patients::Iterator& other)
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            *m_ptr = *other;
            return *this;
        }

        // move assignment
        Iterator& operator=(Iterator&& other) noexcept
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            m_ptr = std::move(other.m_ptr);
            other.m_ptr = nullptr;

            return *this;
        }

        void swap(Iterator& other) {
            std::swap(*m_ptr, *other);
        }

    private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[length]); }

private:
    Patient* m_data;
    int length;

public:
    Patients() {}   // Нужен, потому что в конструкторе билдера ошибка: ГДЕ КОНСТРУКТОР ПО УМОЛЧАНИЮ????
    Patients(int length)
    {
        m_data = new Patient[length];
        this->length = length;
    }
    //Patients(Patients& o) : m_data(o.m_data), length(o.length) {}
    //Patients(Patients&& o) noexcept : m_data(std::move(o.m_data)), length(std::move(o.length)) { o.m_data = nullptr; o.length = 0; }

    // Не могу понять, но он вызывается неявно в конструкторе билдера и ломает все
    //~Patients() { delete[] m_data; std::cout << "destruct " << m_data << "\n"; }
    void clear() { delete[] m_data; }
};

class PatientListBuilder
{
private:
    Patients patients;
    Patients::Iterator curr;

public:
    PatientListBuilder(int length)
    {
        // Я не знаю почему, но так работает
        /*Patients pat = Patients(length);
        curr = pat.begin();
        patients = pat;*/

        // А так нет
        patients = Patients(length);
        curr = patients.begin();
    }

    void add(std::string patientName, std::string report)
    {
        curr->patientName = patientName;
        curr->report = report;
        curr++;
    }

    Patients& get() { return patients; }

};

class Medic : public Employee
{
protected:
    std::string jobTitle;

public:
    Medic(std::string employeeName, double salary, std::string jobTitle) : Employee(employeeName, salary)
    {
        this->profName = "Медик";
        this->jobTitle = jobTitle;
    }

    void Work(Patients& patients)
    {
        std::cout << this->profName << "-" << this->jobTitle << " " << this->employeeName << " выходит на смену.\n";
        double finalSalary = this->salary;
        Patients::Iterator beg = patients.begin();
        Patients::Iterator end = patients.end();
        while (beg != end)
        {
            std::cout << "Прием пациента " << beg->patientName << " с заключением \"" << beg->report << "\".\n";
            this->exp++;
            finalSalary += (salary / 10);
            beg++;
        }
        std::cout << this->profName << "-" << this->jobTitle << " " << this->employeeName << " за смену заработал(а) $" << finalSalary << ".\n";
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    PatientListBuilder builder(3);
    builder.add("Зиновьев Павел", "Неберущийся интеграл");
    builder.add("Ефремов Евгений", "Отсутсвие резолютивного вывода");
    builder.add("Крестникова Ольга", "Несблансированное АВЛ дерево");
    Patients patients = builder.get();
    
    Medic med = Medic("Боровик Анастасия", 50, "Терапевт");
    med.Work(patients);
    patients.clear();
}