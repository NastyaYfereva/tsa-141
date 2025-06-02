#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

int getValue();
double getDouble();
void checkN(const int n);
void checkE(const double e);
double sumN(const int n);
double sumE(const double e);
double getNext(double& current, double& k_fact_sq_plus_next_fact, const int k);

int main()
{
    cout << "Вычисление суммы для ряда: (-1)^k * k / ( (k!)^2 + (k+1)! )" << endl << endl;
    
    cout << "Введите число членов ряда: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма первых " << n << " членов ряда равна " << sumN(n) << endl;
    
    cout << "Введите точность вычислений: ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма членов ряда с точностью " << e << " равна " << sumE(e) << endl;
    
    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

double getDouble()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

void checkN(const int n)
{
    if (n < 1)
    {
        cout << "Ошибка: n должно быть >= 1" << endl;
        abort();
    }
}

void checkE(const double e)
{
    if (e <= 0)
    {
        cout << "Ошибка: e должно быть > 0" << endl;
        abort();
    }
}

double getNext(double& current, double& k_fact_sq_plus_next_fact, const int k)
{
    // Вычисляем новые значения:
    // (k+1)! = (k+1) * k!
    // (k+1)!^2 = (k+1)^2 * (k!)^2
    // (k+2)! = (k+2)*(k+1)!
    
    double next_k_fact_sq_plus_next_fact = pow(k+1, 2) * (k_fact_sq_plus_next_fact - (k+1)) + (k+2)*(k+1)*(k_fact_sq_plus_next_fact - pow(k,2));
    
    double next = -current * (k/(k-1.0)) * 
                 (k_fact_sq_plus_next_fact / next_k_fact_sq_plus_next_fact);
    
    k_fact_sq_plus_next_fact = next_k_fact_sq_plus_next_fact;
    return next;
}

double sumN(const int n)
{
    if (n == 0) return 0;
    
    double k_fact_sq_plus_next_fact = 1*1 + 2; // для k=1: 1!^2 + 2! = 1 + 2 = 3
    double current = -1.0 / 3.0; // первый член при k=1
    double sum = current;
    
    for (int k = 2; k <= n; k++)
    {
        current = getNext(current, k_fact_sq_plus_next_fact, k);
        sum += current;
    }
    
    return sum;
}

double sumE(const double e)
{
    double k_fact_sq_plus_next_fact = 1*1 + 2; // для k=1
    double current = -1.0 / 3.0; // первый член
    double sum = 0.0;
    int k = 1;
    
    while (fabs(current) >= e)
    {
        sum += current;
        k++;
        current = getNext(current, k_fact_sq_plus_next_fact, k);
    }
    
    return sum;
}
