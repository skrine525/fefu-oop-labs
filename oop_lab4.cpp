#include <iostream>

class Employee
{
    protected:
        double salary;    // Зарплата
        double exp;       // Стаж
        bool isExpert;      // Квалифицированный?

    public:
        Employee(double salary, double exp, bool isExpert)
        {
            this->salary = salary;
            this->exp = exp;
            this->isExpert = isExpert;
        }

        double Work(unsigned time)
        {
            double surchargeFactor = 1 + (((int) exp) / 10) / 20;
            unsigned money = time * salary * surchargeFactor;
            exp += time;
            if (isExpert)
                money *= 1.25;
            return money;
        }

        friend bool operator==(const Employee& a, const Employee& b);
};

bool operator==(const Employee& a, const Employee& b)
{
    if (a.isExpert && b.isExpert && a.exp == b.exp && a.salary == b.salary)
        return true;
    else
        return false;
}

enum class MedicType { Surgeon, Therapist, Dentist};
class Medic : public Employee
{
    private:
        MedicType type; // Тип медика

    public:
        Medic(double salary, double exp, bool isExpert, MedicType type) : Employee(salary, exp, isExpert)
        {
            this->type = type;
        }

        double Work(unsigned time)
        {
            if (isExpert)
            {
                double surchargeFactor;
                if (type == MedicType::Surgeon)
                    surchargeFactor = 3;
                else if (type == MedicType::Dentist)
                    surchargeFactor = 2;
                else
                    surchargeFactor = 1.5;

                return Employee::Work(time) * surchargeFactor;
            }
            else
                return 0;
        }
};

#include <iostream>

int main()
{
    Employee emp1(100, 10, true);
    Medic med1(100, 10, true, MedicType::Surgeon);
    std::cout << "emp1 == med1? Result=" << (emp1 == med1) << std::endl;
    std::cout << "med1 made money=" << med1.Work(10) << std::endl;
    std::cout << "emp1 == med1? Result=" << (emp1 == med1) << std::endl;
}