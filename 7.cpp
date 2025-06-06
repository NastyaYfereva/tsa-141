#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

/**
 * @brief Считывает целое значение с клавиатуры с проверкой ввода
 * @return Введенное значение
 * @exception Завершает программу при ошибке ввода
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
 */
void checkN(const int n);

/**
 * @brief Создает новый двумерный массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @return Указатель на созданный массив
 */
int** getNewArray(const size_t m, const size_t n);

/**
 * @brief Выводит двумерный массив на экран
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void printArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заполняет массив значениями вручную
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void fillArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заполняет массив случайными числами в заданном диапазоне
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param start Начало диапазона случайных чисел
 * @param end Конец диапазона случайных чисел
 */
void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end);

/**
 * @brief Освобождает память, занятую двумерным массивом
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void deleteArray(int** array, const size_t m, const size_t n);

/**
 * @brief Создает копию массива
 * @param source Исходный массив
 * @param n,m Размер массива
 * @return Указатель на новый массив-копию
 */
int** copyArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заменяет четные элементы массива нулями
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
int** replaceEvenWithZero(int** array, const size_t m, const size_t n);

/**
 * @brief Находит минимальное значение в строке массива
 * @param row Указатель на строку массива
 * @param n Количество элементов в строке
 * @return Минимальное значение в строке
 */
int findMinInRow(const int* row, const size_t n);

/**
 * @brief Вычисляет количество строк для вставки и новый размер массива
 * @param array Исходный массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param globalMin Глобальный минимум в массиве
 * @return Количество строк для вставки
 */
size_t calculateInsertCount(int** array, size_t m, const size_t n, const int globalMin);

/**
 * @brief Вставляет строки (1,2,3...) после строк, содержащих минимальное значение
 * @param array Указатель на исходный массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param globalMin Глобальный минимум в массиве
 * @param insertCount Количество строк для вставки
 * @return Указатель на новый массив и его новый размер через pair
 */
pair<int**, size_t> insertRowsAfterMin(int** array, size_t m, const size_t n, const int globalMin, const size_t insertCount);

/**
 * @brief Перечисление для выбора способа заполнения массива
 * @param RANDOM Заполнение случайными числами (значение 5)
 * @param MANUAL Ручное заполнение (значение 6)
 */
enum {RANDOM = 5, MANUAL = 6};

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении
 */
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8")
    cout << "Введите M: ";
    size_t m = getSize();
    cout << "Введите N: ";
    size_t n = getSize();
    
    int** array = getNewArray(m, n);
    
    cout << "Введите вариант заполнения массива: " << (int)MANUAL <<
        " заполнить вручную, " << (int)RANDOM << " заполнить случайно: ";
    int choice = getValue();
    
    int start = 0, end = 0;
    switch (choice)
    {    
        case RANDOM:
            cout << "Введите начальное значение: ";
            start = getValue();
            cout << "Введите конечное значение: ";
            end = getValue();
            if (start >= end) 
            {
                cout << "Ошибка: Начальное значение должно быть меньше конечного." << endl;
                deleteArray(array, m, n);
                return 1;
            }
            fillRandom(array, m, n, start, end);
            break;
        case MANUAL:
            fillArray(array, m, n);
            break;
        default:
            cout << "Ошибка" << endl;
            deleteArray(array, m, n);
            return 1;
    }
    
    cout << "Исходный массив:" << endl;
    printArray(array, m, n);
    
    int** array1 = replaceEvenWithZero(array, m, n);
    cout << "Массив после перестановки элементов:" << endl;
    printArray(array1, m, n);
    
    // Находим минимальные значения в каждой строке
    int* rowMins = new int[m];
    for (size_t i = 0; i < m; i++)
    {
        rowMins[i] = findMinInRow(array1[i], n);
    }
    
    // Находим глобальный минимум во всем массиве
    int globalMin = rowMins[0];
    for (size_t i = 1; i < m; i++)
    {
        if (rowMins[i] < globalMin)
        {
            globalMin = rowMins[i];
        }
    }
    
    size_t insertCount = calculateInsertCount(array1, m, n, globalMin);
    auto result = insertRowsAfterMin(array1, m, n, globalMin, insertCount);
    int** array2 = result.first;
    size_t newM = result.second;
    
    cout << "Массив после вставки столбцов" << endl;
    printArray(array2, newM, n);
    
    deleteArray(array, m, n);
    deleteArray(array1, m, n);
    deleteArray(array2, newM, n);
    delete[] rowMins;
    
    return 0;
}

size_t calculateInsertCount(int** array, size_t m, const size_t n, int globalMin)
{
    size_t insertCount = 0;
    for (size_t i = 0; i < m; i++)
    {
        if (findMinInRow(array[i], n) == globalMin)
        {
            insertCount++;
        }
    }
    return insertCount;
}

pair<int**, size_t> insertRowsAfterMin(int** array, size_t m, const size_t n, int globalMin, size_t insertCount)
{
    size_t newM = m + insertCount;
    int** newArray = getNewArray(newM, n);
    
    size_t newRow = 0;
    for (size_t i = 0; i < m; i++)
    {
        // Копируем текущую строку
        for (size_t j = 0; j < n; j++)
        {
            newArray[newRow][j] = array[i][j];
        }
        newRow++;
        
        // Если в строке был глобальный минимум, вставляем новую строку
        if (findMinInRow(array[i], n) == globalMin)
        {
            for (size_t j = 0; j < n; j++)
            {
                newArray[newRow][j] = j + 1; // 1, 2, 3, ..., n
            }
            newRow++;
        }
    }
    
    return make_pair(newArray, newM);
}

int** replaceEvenWithZero(int** array, const size_t m, const size_t n)
{
    int** newArray = copyArray(array, m, n);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (newArray[i][j] % 2 == 0)
            {
                newArray[i][j] = 0;
            }
        }
    }
    return newArray;
}

int findMinInRow(const int* row, const size_t n)
{
    int minVal = row[0];
    for (size_t j = 1; j < n; j++)
    {
        if (row[j] < minVal)
        {
            minVal = row[j];
        }
    }
    return minVal;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка" << endl;
        abort();
    }
    return value;
}

size_t getSize()
{
    int n = getValue();
    checkN(n);
    return (size_t)n;
}

void checkN(const int n)
{
    if (n <= 0)
    {
        cout << "Ошибка" << endl;
        abort();
    }
}

int** getNewArray(const size_t m, const size_t n)
{
    int** array = new int*[m];
    for (size_t i = 0; i < m; i++)
    {
        array[i] = new int[n];
    }
    return array;
}

void printArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

void fillArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << "Enter array[" << i << "," << j << "] = ";
            array[i][j] = getValue();
        }
    }
}

void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end)
{
    srand(time(0));
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            array[i][j] = rand() % (end - start + 1) + start;
        }
    }
}

void deleteArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}

int** copyArray(int** array, const size_t m, const size_t n)
{
    int** newArray = getNewArray(m, n);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}
