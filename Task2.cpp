#include <iostream>

using namespace std;

/**
 * @brief Конвертирует сантиметры в дюймы
 * @param cm Длина в сантиметрах
 * @return Длина в дюймах
 */
double convertToInches(double cm) 
{
    return cm / 2.5; // 1 дюйм = 2.5 см
}

/**
 * @brief Точка входа в программу
 * @return 0 в случае успешного выполнения
 */
int main() 
{
    cout << "Перевод сантиметров в дюймы" << endl;
    cout << "1 дюйм = 2.5 см" << endl;
    
    double centimeters;
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
