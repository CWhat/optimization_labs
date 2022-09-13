#include <iostream>
#include <fstream>

#include <cmath>
#include <utility>
#include <functional>

/*
Функция:
Begin
    R1 := Exp((Degree(x,4)+Degree(x,2)-x+Sqrt(5))/5);
    R2 := Soh((Degree(x,3)+21*x+9)/(21*x+6));
    VarF := R1+R2-3.0;
End;

Найти:
1. Точку минимума
2. Минимальное значение целевой функции
ε=0,01; ε=0,000001 и ε=10^-17
Вывести кол-во итераций и кол-во вычисленных значений целевой ф-и.

График изменения интервалов неопределенности.
Объяснить полученные результаты. Работа должна заканчиваться выводами.
*/

// Кол-во вызовов целевой функции
size_t fCount = 0;

double f(double x)
{
    fCount++;

    double r1 = exp((pow(x, 4.0) + pow(x, 2.0) - x + sqrt(5.0)) / 5.0);
    double r2 = sinh((pow(x, 3.0) + 21.0 * x + 9.0) / (21.0 * x + 6.0));
    return r1 + r2 - 3.0;
}

// для вывода интервалов неопределенностей, точки минимума и минимума; для графика интервалов неопределенностей
std::ofstream out;

// счетчик итераций
size_t iterCount = 0;

// метод дихотомии
std::pair<double, double> dichotomy(std::function<double(double)> func, double a, double b, double eps)
{
    double ak = a;
    double bk = b;
    double lk = b - a;

    double delta = eps * 4.0 / 9.0;
    // double delta = eps / 3.0;

    ////
    out << ak << " " << bk << std::endl;
    iterCount++;
    ////

    while (lk >= eps)
    {
        double xk1 = (ak + bk) / 2.0 - delta;
        double xk2 = (ak + bk) / 2.0 + delta;
        double fxk1 = func(xk1);
        double fxk2 = func(xk2);

        if (fxk1 < fxk2)
            bk = xk2;
        else
            ak = xk1;

        lk = bk - ak;

        ////
        out << ak << " " << bk << std::endl;
        iterCount++;
        ////
        if (iterCount >= 100)
            break;
    }

    double x = (ak + bk) / 2.0;
    double fx = func(x);

    return std::make_pair(x, fx);
}

const double tau1 = 2.0 / (3.0 + sqrt(5.0));
const double tau2 = 2.0 / (1.0 + sqrt(5.0));

// метод золотого сечения
std::pair<double, double> goldenSectionSearch(std::function<double(double)> func, double a, double b, double eps)
{
    double ak = a;
    double bk = b;
    double lk = b - a;

    // double xk1 = ak + 2.0 / (3.0 + sqrt(5.0)) * (bk - ak);
    // double xk2 = ak + 2.0 / (1.0 + sqrt(5.0)) * (bk - ak);
    double xk1 = ak + tau1 * (bk - ak);
    double xk2 = ak + tau2 * (bk - ak);
    double fxk1 = func(xk1);
    double fxk2 = func(xk2);

    ////
    out << ak << " " << bk << std::endl;
    iterCount++;
    ////

    while (lk >= eps)
    {
        if (fxk1 < fxk2)
        {
            bk = xk2;
            xk2 = xk1;
            fxk2 = fxk1;

            // xk1 = ak + 2.0 / (3.0 + sqrt(5.0)) * (bk - ak);
            xk1 = ak + tau1 * (bk - ak);
            fxk1 = func(xk1);
        }
        else
        {
            ak = xk1;
            xk1 = xk2;
            fxk1 = fxk2;

            // xk2 = ak + 2.0 / (1.0 + sqrt(5.0)) * (bk - ak);
            xk2 = ak + tau2 * (bk - ak);
            fxk2 = func(xk2);
        }

        lk = bk - ak;

        ////
        out << ak << " " << bk << std::endl;
        iterCount++;
        ////
        if (iterCount >= 100)
            break;
    }

    double x = (ak + bk) / 2.0;
    double fx = func(x);

    return std::make_pair(x, fx);
}

int main()
{
    out.open("pointsDich.txt");
    out.precision(16);

    std::cout << std::fixed;
    std::cout.precision(16);

    double a = 0.0, b = 1.0;

    // double eps = 0.01;
    double eps = 0.000001;
    // зацикливается
    // double eps = 1e-17;

    auto resDich = dichotomy(f, a, b, eps);

    std::cout << "---Метод дихотомии---" << std::endl;
    std::cout << "Точка минимума: " << resDich.first << std::endl;
    std::cout << "Минимум: " << resDich.second << std::endl;
    std::cout << "Кол-во итераций: " << iterCount << std::endl;
    std::cout << "Кол-во вызовов функции: " << fCount << std::endl;

    out << resDich.first << " " << resDich.second << std::endl;

    out.close();
    iterCount = 0;
    fCount = 0;
    out.open("pointsGold.txt");
    out.precision(16);

    auto resGold = goldenSectionSearch(f, a, b, eps);

    std::cout << "---Метод золотого сечения---" << std::endl;
    std::cout << "Точка минимума: " << resGold.first << std::endl;
    std::cout << "Минимум: " << resGold.second << std::endl;
    std::cout << "Кол-во итераций: " << iterCount << std::endl;
    std::cout << "Кол-во вызовов функции: " << fCount << std::endl;

    out << resGold.first << " " << resGold.second << std::endl;

    out.close();
}