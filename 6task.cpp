#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

/**
 * @brief Безопасное чтение целого числа с клавиатуры
 * @return Введенное целое число
 * @throws abort() при некорректном вводе
 */
int getValue();

/**
 * @brief Получение и проверка размера массива
 * @return Размер массива (size_t)
 * @throws abort() если размер <= 0
 */
size_t getSize();

/**
 * @brief Проверка корректности размера массива
 * @param n Проверяемый размер массива
 * @throws abort() если n <= 0
 */
void checkN(const int n);

/**
 * @brief Заполнение массива значениями
 * @param arr Указатель на массив
 * @param n Размер массива
 * @throws abort() при неверном выборе режима или выходе за диапазон
 */
void fillArray(int* arr, const size_t n);

/**
 * @brief Вывод массива на экран
 * @param arr Указатель на массив (константный)
 * @param n Размер массива
 */
void printArray(const int* arr, const size_t n);

/**
 * @brief Поиск максимального по модулю элемента
 * @param arr Указатель на массив (константный)
 * @param n Размер массива
 * @return Элемент с максимальным абсолютным значением
 */
int findMaxAbs(const int* arr, const size_t n);

/**
 * @brief Замена предпоследнего элемента на максимальный по модулю
 * @param arr Указатель на массив
 * @param n Размер массива
 */
void replacePenultimateWithMaxAbs(int* arr, const size_t n);

/**
 * @brief Подсчет элементов, делящихся на N без остатка
 * @param arr Указатель на массив (константный)
 * @param n Размер массива
 * @param N Делитель
 * @return Количество подходящих элементов
 */
int countDivisibleByN(const int* arr, const size_t n, const int N);

/**
 * @brief Поиск первой пары соседних элементов с разными знаками
 * @param arr Указатель на массив (константный)
 * @param n Размер массива
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int findFirstPairWithDifferentSigns(const int* arr, const size_t n);

/**
 * @brief Создание копии массива
 * @param source Указатель на исходный массив (константный)
 * @param n Размер массива
 * @return Указатель на новый массив-копию
 */
int* copyArray(const int* source, const size_t n);

// Константы для выбора режима заполнения
const int RANDOM = 1; ///< Режим случайного заполнения
const int MANUALY = 2; ///< Режим ручного заполнения

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении
 */
int main()
{
    size_t n = getSize();
    int* arr = new int[n];
    fillArray(arr, n);

    cout << "Original array: ";
    printArray(arr, n);

    int* copiArr = copyArray(arr, n);

    replacePenultimateWithMaxAbs(copiArr, n);
    cout << "Array after replacing penultimate element with max absolute value: ";
    printArray(copiArr, n);

    cout << "Enter N for task 2: ";
    int N = getValue();
    if (N == 0) 
    {
        cout << "Error: Cannot divide by zero!" << endl;
    }
    else 
    {
        int count = countDivisibleByN(copiArr, n, N);
        cout << "Number of elements divisible by N: " << count << endl;
    }

    int pairIndex = findFirstPairWithDifferentSigns(copiArr, n);
    if (pairIndex == -1) {
        cout << "No such pair found." << endl;
    }
    else 
    {
        cout << "First pair index with different signs: " << pairIndex << endl;
    }

    delete[] arr;
    delete[] copiArr;
    return 0;
}

void printArray(const int* arr, const size_t n) 
{
    for (size_t i = 0; i < n; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findMaxAbs(const int* arr, const size_t n) 
{
    if (n == 0) return 0;

    int maxAbs = abs(arr[0]);
    int maxValue = arr[0];

    for (size_t i = 1; i < n; i++) 
    {
        if (abs(arr[i]) > maxAbs) 
        {
            maxAbs = abs(arr[i]);
            maxValue = arr[i];
        }
    }
    return maxValue;
}

int countDivisibleByN(const int* arr, const size_t n, const int N) 
{
    if (N == 0) return 0;

    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] % N == 0)
        {
            count++;
        }
    }
    return count;
}

int findFirstPairWithDifferentSigns(const int* arr, const size_t n) 
{
    for (size_t i = 0; i < n - 1; i++) {
        if ((arr[i] >= 0 && arr[i + 1] < 0) || (arr[i] < 0 && arr[i + 1] >= 0)) 
        {
            return i;
        }
    }
    return -1;
}

int* copyArray(const int* source, const size_t n)
{
    int* newArray = new int[n];
    for (size_t i = 0; i < n; i++)
    {
        newArray[i] = source[i];
    }
    return newArray;
}
