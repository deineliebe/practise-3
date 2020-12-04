#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <iostream>

void show_matrix(int* arr, int matrix_size)
{
    //Находится текущая координата по оси y
    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            std::cout << arr[(i * matrix_size) + j] << ' ';
        }
        std::cout << '\n';
    }
}

//Подпрограмма для заполнения массива "змейкой"
void fill_like_snake(int arr[100], int matrix_size)
{
    //Указатель указывает на первый (нулевой) элемент массива
    int* ptr = arr;
    //Начало работы с координатами консоли
    CONSOLE_SCREEN_BUFFER_INFO info_y;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
    //Находится текущая координата по оси y
    int y_coord = info_y.dwCursorPosition.Y + 1;
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < matrix_size; i++)
    {
        //Цикл идёт от 0 до значения, равного размеру матрицы, не включительно
        //Если число чётное, цикл идёт "вниз"
        if (!(i % 2))
        {
            for (int j = 0; j < matrix_size; j++)
            {
                //Элементу массива через указатель присваивается случайное значение
                *ptr = rand() % (matrix_size * matrix_size) + 1;
                //Выставляется координата х: число 4 выбрано, чтобы был пробел даже выбралось 100
                position.X = i * 4;
                //Выставляется координата y: к заранее найденной переменной y_coord добавляется j
                position.Y = y_coord + j;
                //Курсор выставляется в установленную позицию
                SetConsoleCursorPosition(hConsole, position);
                std::cout << *ptr;
                //Задержка для анимации
                Sleep(150);
                //Указатель перемещается вперёд на значение переменной размера матрицы
                //Если указатель указывал на arr[0], он начинает указывать на arr[6]
                //Это сильнее заметно при выводе
                ptr += matrix_size;
            }
            ptr -= matrix_size;
        }
        else
        {
            //Если число чётное, цикл идёт "вверх"
            for (int j = (matrix_size - 1); j > -1; j--)
            {
                *ptr = rand() % (matrix_size * matrix_size) + 1;
                position.X = i * 4;
                position.Y = y_coord + j;
                SetConsoleCursorPosition(hConsole, position);
                std::cout << *ptr;
                Sleep(150);
                //Указатель перемещается назад на значение переменной размера матрицы
                //Если указатель указывал на arr[6], он начинает указывать на arr[0]
                ptr -= matrix_size;
            }
            ptr += matrix_size;
        }
        //Указатель перемещается вперёд на единицу
        //Если указатель указывал на arr[0], он начинает указывать на arr[1]
        ptr += 1;
    }
    //Устанавливаются новые координаты
    position.X = 0;
    position.Y = y_coord + matrix_size;
    SetConsoleCursorPosition(hConsole, position);
}

//Подпрограмма для заполнения массива спиралью
void spiral_filling(int* arr, short unsigned int matrix_size)
{
    int* ptr = arr;
    CONSOLE_SCREEN_BUFFER_INFO info_y;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
    int y_coord = info_y.dwCursorPosition.Y + 1;
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < matrix_size / 2; i++)
    {
        //Вначале алгоритм ведёт по верхней стороне - от i до matrix_size - i
        for (int j = 0; j < (matrix_size - i * 2 - 1); j++)
        {
            *ptr = rand() % (matrix_size * matrix_size) + 1;
            position.X = (j + i) * 4;
            position.Y = y_coord + i;
            SetConsoleCursorPosition(hConsole, position);
            std::cout << *ptr;
            Sleep(150);
            //Указатель каждую итерацию переносится на следующий элемент массива
            ptr++;
        }
        //Тут алгоритм ведёт по правой стороне
        for (int j = 0; j < (matrix_size - i * 2 - 1); j++)
        {
            *ptr = rand() % (matrix_size * matrix_size) + 1;
            position.X = (matrix_size - i - 1) * 4;
            position.Y = y_coord + (i + j);
            SetConsoleCursorPosition(hConsole, position);
            std::cout << *ptr;
            Sleep(150);
            //Указатель каждую итерацию переносится вперёд на значение, равное размеру массива
            ptr += matrix_size;
        }
        //Алгоритм ведёт по нижней стороне
        for (int j = (matrix_size - i * 2 - 1); j > 0; j--)
        {
            *ptr = rand() % (matrix_size * matrix_size) + 1;
            position.X = (i + j) * 4;
            position.Y = y_coord + matrix_size - 1 - i;
            SetConsoleCursorPosition(hConsole, position);
            std::cout << *ptr;
            Sleep(150);
            ptr--;
        }
        //Алгоритм ведёт по левой стороне
        for (int j = (matrix_size - i * 2 - 1); j > 0; j--)
        {
            *ptr = rand() % (matrix_size * matrix_size) + 1;
            position.X = i * 4;
            position.Y = y_coord + (j + i);
            SetConsoleCursorPosition(hConsole, position);
            std::cout << *ptr;
            Sleep(150);
            ptr -= matrix_size;
        }
        ptr += matrix_size + 1;
    }
    position.X = 0;
    position.Y = y_coord + matrix_size;
    SetConsoleCursorPosition(hConsole, position);
}

void circle_changing(int* arr, int matrix_size)
{
    int temp;
    int* ptr = arr;
    for (int i = 0; i < (matrix_size / 2); i++)
    {
        for (int j = 0; j < (matrix_size / 2); j++)
        {
            temp = *(ptr + (i * matrix_size) + j);
            *(ptr + (i * matrix_size) + j) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j);
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2));
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2)) = *(ptr + (i * matrix_size) + j + (matrix_size / 2));
            *(ptr + (i * matrix_size) + j + (matrix_size / 2)) = temp;
        }
    }
}

void cross_changing(int* arr, int matrix_size)
{
    int temp;
    int* ptr = arr;
    for (int i = 0; i < (matrix_size / 2); i++)
    {
        for (int j = 0; j < (matrix_size / 2); j++)
        {
            temp = *(ptr + (i * matrix_size) + j);
            *(ptr + (i * matrix_size) + j) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2));
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2)) = temp;
            temp = *(ptr + ((i + matrix_size / 2) * matrix_size) + j);
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j) = *(ptr + (i * matrix_size) + j + (matrix_size / 2));
            *(ptr + (i * matrix_size) + j + (matrix_size / 2)) = temp;
        }
    }
}

void vertical_changing(int* arr, int matrix_size)
{
    int temp;
    int* ptr = arr;
    for (int i = 0; i < (matrix_size / 2); i++)
    {
        for (int j = 0; j < (matrix_size / 2); j++)
        {
            temp = *(ptr + (i * matrix_size) + j);
            *(ptr + (i * matrix_size) + j) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j);
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j) = temp;
            temp = *(ptr + (i * matrix_size) + j + (matrix_size / 2));
            *(ptr + (i * matrix_size) + j + (matrix_size / 2)) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2));
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2)) = temp;
        }
    }
}

void horizontal_changing(int* arr, int matrix_size)
{
    int temp;
    int* ptr = arr;
    for (int i = 0; i < (matrix_size / 2); i++)
    {
        for (int j = 0; j < (matrix_size / 2); j++)
        {
            temp = *(ptr + (i * matrix_size) + j);
            *(ptr + (i * matrix_size) + j) = *(ptr + (i * matrix_size) + j + (matrix_size / 2));
            *(ptr + (i * matrix_size) + j + (matrix_size / 2)) = temp;
            temp = *(ptr + ((i + matrix_size / 2) * matrix_size) + j);
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j) = *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2));
            *(ptr + ((i + matrix_size / 2) * matrix_size) + j + (matrix_size / 2)) = temp;
        }
    }
}

//Сортировка пузырьком с помощью указателей
void sort_matrix(int* arr, int matrix_size)
{
    int* ptr1 = arr;
    int* ptr2 = arr;
    int temp;
    for (int i = 0; i < (matrix_size * matrix_size); i++)
    {
        for (int j = i + 1; j < (matrix_size * matrix_size); j++)
        {
            if (*ptr1 > *ptr2)
            {
                temp = *ptr1;
                *ptr1 = *ptr2;
                *ptr2 = temp;
            }
            ptr2++;
        }
        ptr1++;
        ptr2 = ptr1 + 1;
    }
    show_matrix(arr, matrix_size);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Привет!\n";
    int number = 5;
    srand(time(NULL));
    std::cout << "\n1. Используя арифметику указателей, заполнить квадратичную целочисленную матрицу порядка N (6,8,10) случайными числами от 1 до  N*N по двум схемам.\n";
    std::cout << "2. Получить новую матрицу, из матрицы п. 1, переставляя ее блоки в соответствии с четырьмя схемами.\n";
    std::cout << "3. Используя арифметику указателей, отсортировать элементы любой сортировкой.\n";
    std::cout << "4. Уменьшает, увеличивает, умножает или делит все элементы матрицы на введенное пользователем число.\n";
    std::cout << "0. Завершить программу.\n";
    bool if_arr, filling_method;
    //Массив из 100 элементов - в данном варианте он одномерный и статический
    int arr[100];
    if_arr = 0;
    int matrix_size, change_number, operation_number;
    try {
        //Цикл длится пока массив не заполнится в первый раз
        //Это важно, так как пункты 2-4 завязаны на работе с матрицами
        while (!if_arr)
        {
            std::cout << "\n1. Используя арифметику указателей, заполнить квадратичную целочисленную матрицу порядка N (6,8,10) случайными числами от 1 до  N*N по двум схемам.\n";
            std::cout << "Выберите число: 6, 8, 10: ";
            //Переменная, отвечающая за размер матрицы
            std::cin >> matrix_size;
            if (!std::cin) throw "ex";
            if ((matrix_size == 6) or (matrix_size == 8) or (matrix_size == 10))
            {
                std::cout << "Нажмите 0, если хотите вывести матрицу спиралью, 1 - если змейкой: ";
                std::cin >> filling_method;
                if (!std::cin) throw "ex";
                if (filling_method) fill_like_snake(arr, matrix_size);
                else spiral_filling(arr, matrix_size);
                if_arr = 1;
            }
            else
            {
                std::cout << "Вы ввели некорректное число\n";
            }
        }
        while (number != 0)
        {
            std::cout << "\nВыбери номер: ";
            std::cin >> number;
            if (!std::cin)
            {
                throw "ex";
            }
            std::cout << '\n';
            switch (number)
            {
            case 1: std::cout << "\n1. Используя арифметику указателей, заполнить квадратичную целочисленную матрицу порядка N (6,8,10) случайными числами от 1 до  N*N по двум схемам.\n";
                std::cout << "Выберите число: 6, 8, 10: ";
                std::cin >> matrix_size;
                if (!std::cin) throw "ex";
                if ((matrix_size == 6) or (matrix_size == 8) or (matrix_size == 10))
                {
                    std::cout << "Нажмите 0, если хотите вывести матрицу спиралью, 1 - если змейкой: ";
                    std::cin >> filling_method;
                    if (!std::cin) throw "ex";
                    if (filling_method)
                    {
                        fill_like_snake(arr, matrix_size);
                    }
                    else
                    {
                        spiral_filling(arr, matrix_size);
                    }
                }
                else
                {
                    std::cout << "Вы ввели некорректное число\n";
                }
                break;
            case 2: "\n2. Получить новую матрицу, из матрицы п. 1, переставляя ее блоки в соответствии с четырьмя схемами.\n";
                std::cout << "Выберите метод перестановки: по кругу (a) - 1, крестом (b) - 2, по вертикали (c) - 3, по горизонтали (d) - 4: ";
                std::cin >> change_number;
                if (!std::cin) throw "ex";
                switch (change_number)
                {
                case 1: circle_changing(arr, matrix_size);
                    show_matrix(arr, matrix_size);
                    break;
                case 2: cross_changing(arr, matrix_size);
                    show_matrix(arr, matrix_size);
                    break;
                case 3: vertical_changing(arr, matrix_size);
                    show_matrix(arr, matrix_size);
                    break;
                case 4: horizontal_changing(arr, matrix_size);
                    show_matrix(arr, matrix_size);
                    break;
                default:
                    std::cout << "Неккоректное значение\n";
                    break;
                }
                break;
            case 3: std::cout << "3. Используя арифметику указателей, отсортировать элементы любой сортировкой.\n";
                sort_matrix(arr, matrix_size);
                break;
            case 4: std::cout << "4. Уменьшает, увеличивает, умножает или делит все элементы матрицы на введенное пользователем число.\n";
                std::cout << "Выберите операцию: уменьшить - 1, увеличить - 2, умножить - 3, поделить - 4: ";
                std::cin >> change_number;
                if (!std::cin) throw "ex";
                switch (change_number)
                {
                case 1:
                    std::cout << "Выберите число: ";
                    std::cin >> operation_number;
                    if (!std::cin) throw "ex";
                    for (int i = 0; i < (matrix_size * matrix_size); i++)
                    {
                        arr[i] -= operation_number;
                    }
                    show_matrix(arr, matrix_size);
                    break;
                case 2:
                    std::cout << "Выберите число: ";
                    std::cin >> operation_number;
                    if (!std::cin) throw "ex";
                    for (int i = 0; i < (matrix_size * matrix_size); i++)
                    {
                        arr[i] += operation_number;
                    }
                    show_matrix(arr, matrix_size);
                case 3:
                    std::cout << "Выберите число: ";
                    std::cin >> operation_number;
                    if (!std::cin) throw "ex";
                    for (int i = 0; i < (matrix_size * matrix_size); i++)
                    {
                        arr[i] *= operation_number;
                    }
                    show_matrix(arr, matrix_size);
                    break;
                case 4: 
                    std::cout << "Выберите число: ";
                    std::cin >> operation_number;
                    if (!std::cin) throw "ex";
                    if (operation_number == 0) throw "ex";
                    for (int i = 0; i < (matrix_size * matrix_size); i++)
                    {
                        arr[i] /= operation_number;
                    }
                    show_matrix(arr, matrix_size);
                    break;
                default: std::cout << "Неккоректное значение\n";
                    break;
                }
                break;
            }
        }
    }
    catch (...)
    {
        std::cout << "\nНекорректные данные!\n";
    }
}
