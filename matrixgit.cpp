#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

bool already = false;

void randomMatriks(int fiks)
{
    int hmm = 0;
    const int length = fiks * fiks + (fiks * fiks - 1);
    char result[length];
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        if (i % 2 == 0)
        {
            result[i] = 48 + rand() % 10;
        }
        else
        {
            result[i] = 32;
        }
        hmm++;
    }
    OpenClipboard(0);
    EmptyClipboard();
    const char *op = result;
    const int ln = strlen(op) + 1;
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, ln);
    memcpy(GlobalLock(h), op, ln);
    GlobalUnlock(h);
    SetClipboardData(CF_TEXT, h);
    CloseClipboard();
}

void MakeArr(int **q, int **r, int **s, int ordo)
{
    for (int i = 0; i < ordo; i++)
    {
        q[i] = new int[ordo];
        r[i] = new int[ordo];
        s[i] = new int[ordo];
    }
    for (int i = 0; i < ordo; i++)
    {
        for (int j = 0; j < ordo; j++)
        {
            cin >> q[i][j];
        }
    }
}

void printArr(int ordo, int **q)
{
    for (int i = 0; i < ordo; i++)
    {
        for (int j = 0; j < ordo; j++)
        {
            cout << "\t" << q[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void printArr(int ordo, float **q)
{
    for (int i = 0; i < ordo; i++)
    {
        for (int j = 0; j < ordo; j++)
        {
            cout << "\t" << q[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

void calculate(char with, char oper, int **q, int **r, int **s, int ordo)
{
    int scalar;
    if ((oper == '+' || oper == '-') && (with == 'S'))
    {
        cout << "Can't Do Operation Using Scalar\n";
        system("pause");
        return;
    }
    else if (oper == '*' && with == 'S')
    {
        cout << "Input Scalar Value : ";
        cin >> scalar;
        cout << "Result : \n";
        for (int i = 0; i < ordo; i++)
        {
            for (int j = 0; j < ordo; j++)
            {
                s[i][j] = scalar * q[i][j];
            }
        }
        printArr(ordo, s);
        system("pause");
        return;
    }
    else
    {
        cout << "Input Matrix " << ordo << "x" << ordo << " :\n";
        for (int i = 0; i < ordo; i++)
        {
            for (int j = 0; j < ordo; j++)
            {
                cin >> r[i][j];
            }
        }
        if (oper == '+')
        {
            for (int i = 0; i < ordo; i++)
            {
                for (int j = 0; j < ordo; j++)
                {
                    s[i][j] = r[i][j] + q[i][j];
                }
            }
        }
        else if (oper == '-')
        {
            for (int i = 0; i < ordo; i++)
            {
                for (int j = 0; j < ordo; j++)
                {
                    s[i][j] = q[i][j] - r[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < ordo; i++)
            {
                for (int j = 0; j < ordo; j++)
                {
                    s[i][j] = 0;
                    for (int k = 0; k < ordo; k++)
                    {
                        s[i][j] += q[i][k] * r[k][j];
                    }
                }
            }
        }
        cout << "\n";
        printArr(ordo, s);
        system("pause");
        return;
    }
}

char with(int **q, int ordo)
{
    char with;
    int choose;
    system("cls");
    printArr(ordo, q);
    cout << "1. With Scalar\n";
    cout << "2. With Matrix\n";
    cout << "0. Back\n";
    cout << "Enter Your Choice : ";
    cin >> choose;
    if (choose == 1)
    {
        with = 'S';
    }
    else if (choose == 2)
    {
        with = 'M';
    }
    else
    {
        return '0';
    }
    return with;
}

char oper(int **q, int ordo)
{
    int choose;
    char oper;
    system("cls");
    printArr(ordo, q);
    cout << "1. Addition\n";
    cout << "2. Substraction\n";
    cout << "3. Multiplication\n";
    cout << "0. Back\n";
    cout << "Enter Your Choice : ";
    cin >> choose;
    if (choose == 1)
    {
        oper = '+';
    }
    else if (choose == 2)
    {
        oper = '-';
    }
    else if (choose == 3)
    {
        oper = '*';
    }
    else
    {
        return '0';
    }
    return oper;
}

void arithmeticOps(int **q, int **r, int **s, int ordo)
{
    int choose;
    char operr = '-', withh = '-';
    while (true)
    {
        if (operr == '0')
        {
            break;
        }
        operr = oper(q, ordo);
        if (operr == '0')
        {
            continue;
        }
        withh = with(q, ordo);
        if (withh == '0')
        {
            continue;
        }
        randomMatriks(ordo);
        calculate(withh, operr, q, r, s, ordo);
        break;
    }
}

void transpose(int **q, int **r, int ordo)
{
    for (int i = 0; i < ordo; i++)
    {
        for (int j = 0; j < ordo; j++)
        {
            r[i][j] = q[j][i];
        }
    }
}

int determinant(int **q, int ordo)
{
    if (ordo == 2)
    {
        int result = q[0][0] * q[1][1] - q[0][1] * q[1][0];
        return result;
    }
    else
    {
        int ordoMin = ordo - 1;
        int **r = new int *[ordoMin];
        for (int i = 0; i < ordoMin; i++)
        {
            r[i] = new int[ordoMin]; // bikin objek per kolom
        }
        int result, i, a, b;
        result = i = a = b = 0;
        for (int h = 0; h < ordo; h++)
        {
            while (i < ordo)
            {
                for (int j = 0; j < ordo; j++)
                {
                    if (0 != j)
                    {
                        for (int k = 0; k < ordo; k++)
                        {
                            if (i != k)
                            {
                                r[a][b] = q[j][k];
                                b++;
                            }
                        }
                        a++;
                        b = 0;
                    }
                }
                i++;
                a = 0;
                break;
            }
            if (h % 2 == 0)
            {
                result += q[0][h] * determinant(r, ordoMin);
            }
            else
            {
                result += -q[0][h] * determinant(r, ordoMin);
            }
        }
        delete r;
        return result;
    }
}

void minCofAdj(int **q, int **r, int **s, int ordo)
{
    already = true;
    if (ordo == 2)
    {
        if (already)
            cout << "Minor :\n";
        r[0][0] = q[1][1];
        r[0][1] = q[1][0];
        r[1][0] = q[0][1];
        r[1][1] = q[0][0];
        if (already)
            printArr(ordo, r);
        if (already)
            cout << "\nCofactor :\n";
        int t[2][2] = {{1, -1},
                       {-1, 1}};
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                s[i][j] = r[i][j] * t[i][j];
            }
        }
        if (already)
            printArr(ordo, s);
        if (already)
            cout << "\nAdjoint :\n";
        transpose(s, r, 2);
        if (already)
            printArr(ordo, r);
    }
    else
    {
        if (already)
            cout << "Minor :\n";
        int ordoMin = ordo - 1;
        int **p = new int *[ordoMin];
        for (int i = 0; i < ordoMin; i++)
        {
            p[i] = new int[ordoMin]; // bikin objek per kolom
        }
        int hasil, i, a, b, row;     // i
        hasil = i = a = b = row = 0; // i
        for (int g = 0; g < ordo; g++)
        {
            for (int h = 0; h < ordo; h++)
            {
                while (i < ordo)
                {
                    for (int j = 0; j < ordo; j++)
                    {
                        if (row != j)
                        {
                            for (int k = 0; k < ordo; k++)
                            {
                                if (i != k)
                                {
                                    p[a][b] = q[j][k];
                                    // cout << q[j][k] << " " << endl;
                                    b++;
                                }
                            }
                            a++;
                            b = 0;
                        }
                    }
                    a = 0;
                    // cout << s[g][h] << " " << h << " " << i << endl; // masuk posisi minor
                    s[g][h] = determinant(p, ordoMin);
                    i++;
                    break;
                }
            }
            i = 0;
            row++;
            // cout << endl;
        }
        if (already)
            printArr(ordo, s);
        if (already)
            cout << "Cofactor :\n";
        int t[ordo][ordo];
        int height, width;
        height = width = -1;
        for (int i = 0; i < ordo; i++)
        {
            for (int j = 0; j < ordo; j++)
            {
                if (j % 2 != 0)
                {
                    width *= -1;
                }
                t[i][j] = height * width;
                if (j % 2 != 0)
                {
                    width *= -1;
                }
            }
            height *= -1;
        }
        for (int i = 0; i < ordo; i++)
        {
            for (int j = 0; j < ordo; j++)
            {
                s[i][j] = s[i][j] * t[i][j];
            }
        }
        if (already)
            printArr(ordo, s);
        if (already)
            cout << "Adjoint :\n";
        transpose(s, r, ordo);
        if (already)
            printArr(ordo, r);
        delete p;
    }
}

void invers(int **q, int **r, int **s, int ordo, float multi)
{
    float **casting = reinterpret_cast<float **>(s);
    for (int i = 0; i < ordo; i++)
    {
        for (int j = 0; j < ordo; j++)
        {
            casting[i][j] = multi * r[i][j];
        }
    }
    cout << "Invers :\n";
    printArr(ordo, casting);
}

int main()
{
    int choose;
    int ordo;
    int resultDet;
    int **Matrix, **MatrixHelp, **MatrixRes;
// ===== GOTO HERE
top:
    system("cls");
    cout << "Input Square Matrix's Ordo (max recommended : 10) : ";
    cin >> ordo;
    if (ordo < 2)
    {
        cout << "invalid Ordo. Please Try Again !\n";
        system("pause");
        goto top;
    }
    randomMatriks(ordo);
    Matrix = new int *[ordo];
    MatrixHelp = new int *[ordo];
    MatrixRes = new int *[ordo];
    cout << "In Windows, press \"ctrl + v\" for generate random number\n";
    cout << "Input Matrix's Elements : \n";
    MakeArr(Matrix, MatrixHelp, MatrixRes, ordo);
    resultDet = determinant(Matrix, ordo);
    do
    {
        system("cls");
        printArr(ordo, Matrix);
        cout << "Choose Menu :\n";
        cout << "1. Arithmetic Operation\n";
        cout << "2. Minor, Cofactor, Adjoint\n";
        cout << "3. Determinant\n";
        cout << "4. Invers\n";
        cout << "5. Transpose\n";
        cout << "6. Choose Another Ordo\n";
        cout << "0. Exit\n";
        cout << "Enter Your Choice : ";
        cin >> choose;
        if (choose == 1)
        {
            arithmeticOps(Matrix, MatrixHelp, MatrixRes, ordo);
        }
        else if (choose == 2)
        {
            minCofAdj(Matrix, MatrixHelp, MatrixRes, ordo);
            system("pause");
        }
        else if (choose == 3)
        {
            int result = determinant(Matrix, ordo);
            cout << "The Determinant Result is " << result << "\n";
            system("pause");
        }
        else if (choose == 4)
        {
            if (resultDet == 0)
            {
                cout << "There is No Invers, Because of Determinant Value is 0\n";
            }
            else
            {
                float multiplication = 1 / (float)resultDet;
                if (!already)
                {
                    minCofAdj(Matrix, MatrixHelp, MatrixRes, ordo);
                }
                invers(Matrix, MatrixHelp, MatrixRes, ordo, multiplication);
            }

            system("pause");
        }
        else if (choose == 5)
        {
            transpose(Matrix, MatrixHelp, ordo);
            system("pause");
        }
        else if (choose == 6)
        {
            delete Matrix;
            delete MatrixHelp;
            delete MatrixRes;
            goto top;
        }
        else
        {
            choose = 0;
        }
    } while (choose != 0);

    cout << "Finish";

    return 0;
}
