#include <iostream>
#include <cstdlib>
using namespace std;

const int SIZE = 9;
int sudoku[SIZE][SIZE];
int ansfer_sudoku[SIZE][SIZE];
int test_array[SIZE * SIZE][SIZE] = { 0 };
int easy = 2, medium = 39, hard = 45;

bool checkrow(int, int);
bool checkcol(int, int);
bool checksqr(int, int);
bool test(int, int);
bool CheckRepeated(int i, int j);
void moveback(int& i, int& j);
void write(int i, int j);
void print(int arr[SIZE][SIZE]);
void hide(int x, int y, int col_hide);
void start(int level);

int main()
{
    srand(time(0));

    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            for (;; )
            {
                if (!test(i, j))
                    moveback(i, j);

                ansfer_sudoku[i][j] = rand() % 9 + 1;
                sudoku[i][j] = ansfer_sudoku[i][j];

                if (CheckRepeated(i, j))
                    continue;
                
                write(i, j);
                if (checksqr(i, j) && checkrow(i, j) && checkcol(i, j))
                    break;
            }
        }
    }
    print(ansfer_sudoku);
    start(easy);
    int user_i, user_j, user_num;
    
    while (easy != 0)
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                while (true)
                {
                    cout << "Enter coordinates" << endl;
                    cout << "I - "; cin >> user_i;
                    cout << "J - "; cin >> user_j;
                    if (sudoku[user_i][user_j] != 0)
                    {
                        continue;
                    }
                    cout << "Enter your number - "; cin >> user_num;
                    sudoku[user_i][user_j] = user_num;

                    if (ansfer_sudoku[user_i][user_j] == sudoku[user_i][user_j])
                    {
                        easy--;
                        print(sudoku);
                        break;
                    }
                    else
                    {
                        cout << "Error" << endl;
                        sudoku[user_i][user_j] = 0;
                        print(sudoku);
                    }
                }
                if (easy == 0) { break; }
            }
            if (easy == 0) { break; }
        }
    }
    return 0;
}

bool checkrow(int x, int y)
{
    for (int i = 0; i < y; i++)
        if (sudoku[x][i] == sudoku[x][y])
            return false;

    return true;
}

bool checkcol(int x, int y)
{
    for (int i = 0; i < x; i++)
        if (sudoku[i][y] == sudoku[x][y])
            return false;

    return true;
}

bool checksqr(int x, int y)
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

bool test(int i, int j)
{
    int current = i * 9 + j + 1;

    for (int x = 1; x < 9; x++)
        if (test_array[current][x] == 0)
            return true;

    return false;
}

bool CheckRepeated(int i, int j)
{
    int value = sudoku[i][j];
    int current = i * 9 + j + 1;

    if (test_array[current][value] == 1)
        return true;
    else
        return false;
}

void moveback(int& i, int& j)
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

void write(int i, int j)
{
    int current = i * 9 + j + 1;
    int value = sudoku[i][j];
    test_array[current][value] = 1;
}

void print( int arr[SIZE][SIZE])
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
    cout << "=========================\n";
}

void start(int level)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << "=========================\n";

        cout << "| ";

        for (j = 0; j < 9; j++)
        {
            hide(i, j, level-1);
            cout << sudoku[i][j] << " ";
            if ((j + 1) % 3 == 0)
                cout << "| ";
        }

        cout << endl;
    }
    cout << "=========================\n";
}

void hide(int x, int y, int col_hide)
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