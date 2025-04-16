#include <iostream>
#include <limits> 

using namespace std;

// Константа для перевода сантиметров в дюймы
const double CM_TO_INCH = 2.5; // 1 дюйм = 2.5 см

/**
 * @brief Получает корректное положительное число от пользователя
 * @param prompt Приглашение для ввода
 * @return Введенное пользователем положительное число
 */
double getPositiveNumber(const string prompt) 
{
    double value;
    while (true) 
    {
        cout << prompt;
        cin >> value;
        
        if (cin.fail() || value <= 0) 
        {
            cin.clear(); // Сброс флага ошибки
            cout << "Ошибка: введите положительное число!" << endl;
        } else 
        {
            return value;
        }
    }
}

/**
 * @brief Конвертирует сантиметры в дюймы
 * @param cm Длина в сантиметрах
 * @return Длина в дюймах
 */
double convertToInches(double cm) 
{
    return cm / CM_TO_INCH;
}

/**
 * @brief Точка входа в программу
 * @return 0 в случае успешного выполнения
 */
int main() 
{

    cout << "перевод сантиметры в дюймы" << endl;
    cout << "1 дюйм = " << CM_TO_INCH << " см" << endl;
    
    // Получаем длину в сантиметрах
    double centimeters = getPositiveNumber("Введите длину в сантиметрах: ");
    
    // Конвертируем и выводим результат
    double inches = convertToInches(centimeters);
    cout << "Результат: " << centimeters << " см = " << inches << " дюймов" << endl;
    
    return 0;
}
