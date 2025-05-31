#include <iostream>

/**
 * @brief Пространство имен стандартной библиотеки C++
 */
using namespace std;

/**
 * @brief Конвертирует сантиметры в дюймы
 * @param cm Длина в сантиметрах
 * @return Длина в дюймах
 */
double convertToInches(const double cm);

/**
 * @brief Точка входа в программу
 * @return Код возврата: 0 - успешное выполнение, 1 - ошибка ввода
 * @details Программа запрашивает у пользователя длину в сантиметрах
 * и выводит эквивалентное значение в дюймах (1 дюйм = 2.5 см)
 */
int main() 
{
    cout << "Перевод сантиметров в дюймы" << endl;
    cout << "1 дюйм = 2.5 см" << endl;
    
    double centimeters = 0; 
    cout << "Введите длину в сантиметрах: ";
    cin >> centimeters;
    
    if (centimeters <= 0) 
    {
        cout << "Ошибка: введите положительное число!" << endl;
        return 1;
    }
    
    double inches = convertToInches(centimeters);
    cout << "Результат: " << centimeters << " см = " << inches << " дюймов" << endl;
    
    return 0;
}

/**
 * @brief Конвертирует сантиметры в дюймы
 * @param cm Длина в сантиметрах (константный параметр)
 * @return Длина в дюймах
 * @details Используется коэффициент перевода: 1 дюйм = 2.5 см
 */
double convertToInches(const double cm) 
{
    return cm / 2.5;
}
