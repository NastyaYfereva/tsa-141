#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @brief Считывает целое значение с клавиатуры с проверкой ввода
 * @return Введенное значение
 */
int getValue();

/**
 * @brief Получает и проверяет размер массива
 * @return Размер массива
 */
size_t getSize();

/**
 * @brief Проверяет корректность размера массива
 * @param n Проверяемое значение размера
 * @return Завершает программу при n <= 0
 */
void checkN(const int n);

/**
 * @brief Заполняет массив значениями
 * @param arr Указатель на массив
 * @param n Размер массива
 */
void fillArray(int* arr, const size_t n);

/**
 * @brief Находит максимальный элемент массива
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Максимальное значение
 */
void printArray(int* arr, const size_t n);

/**
 * @brief Заменяет предпоследний элемент массива на максимальный
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Выводит изменёный элемент массива
 */
int findMaxAbs(int* arr, const size_t n);

/**
 * @brief Заменяет предпоследний элемент массива на максимальный
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Выводит предупреждение если массив слишком мал или не найдено допустимых элементов для замены
 */
void replacePenultimateWithMaxAbs(int* arr, const size_t n);

/**
 * @brief Считает количество элементов, которые делятся на значение N без остатка
 * @param arr Указатель на массив
 * @param n Размер массива
 * @param N число на которое элемент должен делиться без остатка
 * @return Количество элементов удовлетворяющих условию
 */
int countDivisibleByN(const int* arr, size_t n, const int N);

/**
 * @brief Ищет номер первой пары соседних элементов с разными знаками
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int findFirstPairWithDifferentSigns(const int* arr, size_t n);

/**
 * @brief Создает копию массива
 * @param source Исходный массив
 * @param n Размер массива
 * @return Указатель на новый массив-копию
 */
int* copyArray(const int* copiArr, const size_t n);

/**
* @brief Перечисление для выбора способа заполнения данных
* @param MANUALY Выбор ручного заполнения массива
* @param RANDOM Выбор автоматического заполнения массива
*/
const int RANDOM = 1;
const int MANUALY = 2;

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
    int count = countDivisibleByN(copiArr, n, N);
    cout << "Number of elements divisible by N: " << count << endl;

    int pairIndex = findFirstPairWithDifferentSigns(copiArr, n);
    if (pairIndex == -1)
    {
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

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Invalid input. Aborting." << endl;
        abort();
    }
    return value;
}

size_t getSize()
{
    cout << "Enter n: ";
    int n = getValue();
    checkN(n);
    return size_t(n);
}

void checkN(const int n)
{
    if (n <= 0)
    {
        cout << "Invalid size. Aborting." << endl;
        abort();
    }
}

void fillArray(int* arr, const size_t n)
{
    cout << "Choose input method (" << RANDOM << " - random, " << MANUALY << " - manual): ";
    int choice = getValue();
    switch (choice)
    {
    case RANDOM:
    {
        srand(time(0));
        for (size_t i = 0; i < n; i++)
        {
            int min = -30;
            int max = 70;
            arr[i] = min + rand() % (max - min + 1);
        }
        break;
    }
    case MANUALY:
    {
        for (size_t i = 0; i < n; i++)
        {
            cout << "Enter arr[" << i + 1 << "] (-30 to 70): ";
            int value = getValue();

            if (value >= -30 && value <= 70)
            {
                arr[i] = value;
            }
            else
            {
                cout << "Error! Value must be between -30 and 70" << endl;
                abort();
            }

        }
        break;
    }
    default:
        cout << "Invalid choice. Aborting." << endl;
        abort();
    }
}

void printArray(int* arr, const size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findMaxAbs(int* arr, const size_t n)
{
    int maxAbs = arr[1];
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] > maxAbs)
        {
            maxAbs = arr[i];
        }
    }
    return maxAbs;
}

void replacePenultimateWithMaxAbs(int* arr, const size_t n)
{
    if (n < 2)
    {
        cout << "The array is too small to replace the penultimate element." << endl;
        return;
    }

    int maxAbs = findMaxAbs(arr, n);

    if (maxAbs == arr[1])
    {
        cout << "No valid elements found for replacement." << endl;
    }
    else
    {
        arr[n - 2] = maxAbs;
    }
}

int countDivisibleByN(const int* arr, size_t n, const int N)
{
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

int findFirstPairWithDifferentSigns(const int* arr, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
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