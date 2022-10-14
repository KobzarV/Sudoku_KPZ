#include <iostream>
#include <cstdlib>

using namespace std;

const int SIZE = 9;
int sudoku[SIZE][SIZE];
int ansfer_sudoku[SIZE][SIZE];
int test_array[SIZE * SIZE][SIZE] = { 0 };
enum {easy = 43, medium = 49, hard = 55 };

bool checkrow(int, int);
bool checkcol(int, int);
bool checksqr(int, int);
bool CheckRepeated(int i, int j);
bool test(int, int);
void moveback(int& i, int& j);
void write(int i, int j);
void print(int arr[SIZE][SIZE]);
void hide(int x, int y, int col_hide);
void start(int level);
void menu(int& level);

int main()
{
    setlocale(LC_ALL, "");
    int level = 1;
    int lifes = 3;
    srand(time(0));

    int i, j;
    for (i = 0; i < 9; i++)   //перевірка правильності розміщення чисел в таблиці судоку
    {
        for (j = 0; j < 9; j++)
        {
            for (;; )
            {
                if (!test(i, j))  // перевіряємо місце в таблиці чи воно вільне
                    moveback(i, j);   // якщо зайняте то повертаємось на 1 ітерацію назад

                ansfer_sudoku[i][j] = rand() % 9 + 1;  // присвоюємо значення мисиву з відповідями
                sudoku[i][j] = ansfer_sudoku[i][j];  // присвоюємо таке саме значення ігровому масиву

                if (CheckRepeated(i, j))  // перевірка на повторення присвоєного значення
                    continue;
                
                write(i, j); // в тестовому масиві це значення замінюється на 1, щоб позначити що комірка зайнята
                if (checksqr(i, j) && checkrow(i, j) && checkcol(i, j)) //перевірки рядка, стовпчика і квадрата 3х3 на повторення значень
                    break;
            }
        }
    }
    //print(ansfer_sudoku);  // поле з відповідями (для тестів коду)

    int user_i, user_j, user_num;


    while (true)   // цикл роботи з гравцем
    {
        menu(level);     // меню
        if (level == 0)   // перевірка виходу із цикла
        {
            cout << "Goodbye! Have a nice day!" << endl;
            break;
        }
        else
        {
            cout << "Кількість життів - " << lifes << endl;
            start(level);      // початкове поле
            for (i = 0; i < 9; i++)
            {
                for (j = 0; j < 9; j++)
                {
                    while (true)     // ходи гравців
                    {
                        cout << "Введіть координати комірки" << endl;
                        cout << "I - "; cin >> user_i;
                        cout << "J - "; cin >> user_j;
                        user_i--;  // для зручності вибору користувача
                        user_j--;  // для зручності вибору користувача
                        if (sudoku[user_i][user_j] != 0)  // перевірка вибраної комірки
                        {
                            continue;
                        }
                        cout << "Введіть ваше число - "; cin >> user_num;
                        sudoku[user_i][user_j] = user_num;
                        // перевірка чи правильне число ввів користувач
                        if (ansfer_sudoku[user_i][user_j] == sudoku[user_i][user_j])
                        {
                            level--;
                            cout << "\nКількість життів - " << lifes << endl;
                            print(sudoku);
                            break;
                        }
                        else
                        {
                            cout << "Error" << endl;
                            lifes--;
                            sudoku[user_i][user_j] = 0;
                            cout << "\nКількість життів - " << lifes << endl;
                            print(sudoku);
                        }
                        if (lifes == 0)    // перевірка завершення гри через закінчення життів
                        {
                            cout << "Game Over" << endl;
                            level = 0;
                            break;
                        }
                    }
                    if (level == 0) { break; }
                }
                if (level == 0)  // повідомлення про перемогу 
                {
                    cout << "Вітаємо!! Це була класна гра!\n" << endl;
                    break; 
                }
            }
        }
    }
    return 0;
}

bool checkrow(int x, int y)  // фуннкція перевірки рядка
{
    for (int i = 0; i < y; i++)
        if (sudoku[x][i] == sudoku[x][y])
            return false;

    return true;
}

bool checkcol(int x, int y)   // фуннкція перевірки стовпчика
{
    for (int i = 0; i < x; i++)
        if (sudoku[i][y] == sudoku[x][y])
            return false;

    return true;
}

bool checksqr(int x, int y)  // функція перевірки квадрату (3х3)
{
    int i_start = x / 3;      i_start *= 3;
    int j_start = y / 3;      j_start *= 3;

    for (int i = i_start; i < i_start + 3; i++)
        for (int j = j_start; j < j_start + 3; j++)
        {
            if (i == x && j == y)
                return true;

            if (sudoku[i][j] == sudoku[x][y])
                return false;
        }
    return true;
}

bool test(int i, int j)  // перевірка комірки чи в ній вже є якесь значення
{
    int current = i * 9 + j + 1;

    for (int x = 1; x < 9; x++)
        if (test_array[current][x] == 0)
            return true;

    return false;
}

bool CheckRepeated(int i, int j)  // перевірка на повторення введеного значення
{
    int value = sudoku[i][j];
    int current = i * 9 + j + 1;

    if (test_array[current][value] == 1)
        return true;
    else
        return false;
}

void moveback(int& i, int& j) // функція повернення циклу на 1 ітерацію назад
{
    int current = i * 9 + j + 1;

    for (int x = 1; x <= 9; x++)
        test_array[current][x] = 0;

    if (j < 1)
    {
        i--;    j = 8;
    }
    else
        j--;
}

void write(int i, int j)  //замінює в тестовому масиві елементи на 1 для познацення, що комірка зайнята
{
    int current = i * 9 + j + 1;
    int value = sudoku[i][j];
    test_array[current][value] = 1;
}

void print( int arr[SIZE][SIZE])  // відображення ігрового поля
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << "=========================\n";

        cout << "| ";

        for (j = 0; j < 9; j++)
        {
            cout << arr[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }

        cout << endl;
    }
    cout << "=========================\n\n";
}

void start(int level)  // відображення початкового поля гри (із схованими елементами)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << "=========================\n";

        cout << "| ";

        for (j = 0; j < 9; j++)
        {
            hide(i, j, level-1);  // приховання елемена поля (зміна значення на 0)
            cout << sudoku[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }

        cout << endl;
    }
    cout << "=========================\n";
}

void hide(int x, int y, int col_hide) // функція приховання елемена поля (зміна значення на 0)
{
    int hide_i, hide_j, count = 0;
    srand(time(0));
    for (int i = 0; i < 9 ; i++)
    {
        for (int j = 0; ; j++)
        {
            if (count > col_hide) { break; }
            hide_i = rand() % 9;
            hide_j = rand() % 9;
            sudoku[hide_i][hide_j] = 0;
            count += 1;
        }
    }
}

void menu(int& level)  // функція меню (вибір рівня складності або вихід із гри)
{
    int choise;
    while (true)
    {
        cout << "\tSUDOKU" << endl;
        cout << "1) Легкий рівень" << endl;
        cout << "2) Середній рівень" << endl;
        cout << "3) Складний рівень" << endl;
        cout << "4) Вихід" << endl;
        cout << "Виберіть пункт меню - ";
        cin >> choise;
        if (choise > 0 && choise <= 4) { break; }
    }
    switch (choise)
    {
    case 1:
        level = easy;
        break;
    case 2:
        level = medium;
        break;
    case 3:
        level = hard;
        break;
    case 4:
        level = 0;
        break;
    }
}