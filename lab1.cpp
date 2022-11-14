#include <iostream>
#include <cmath>
#include <limits>

#define M_PI           3.14159265358979323846  /* pi */

double f(double x, int n);

int main()
{
    double x;
    int n;

    std::cout << "x=";
    std::cin >> x;
    if(std::cin.fail())
    {
        std::cout << "Invalid input." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }

    std::cout << "n=";
    std::cin >> n;
    if(std::cin.fail())
    {
        std::cout << "Invalid input." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }

    if(x == -1)
        std::cout << "Invalid x value" << std::endl;
    else if(n < 5)
        std::cout << "Valid n value: n>=5" << std::endl;
    else
        std::cout << "f(x, n)=" << f(x, n) << std::endl;

    return 0;
}

double f(double x, int n)
{
    double y = 1;

    for(int i = 5; i <= n; i++)
    {
        y *= 1+(x*log(i))/((x+1)/(1+pow(i, 2)));
    }
    y += sin(M_PI);

    return y;
}
