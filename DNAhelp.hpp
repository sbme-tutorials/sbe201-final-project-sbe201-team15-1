#ifndef DNAHELP_HPP
#define DNAHELP_HPP
#include <map>
#include <string>
#include <cmath>
#include <iostream>
namespace DNAH
{

//I thought I may need to sort some arrays :3
void bubbleSortDescend(int *a, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (a[i] < a[j])
            {
                a[i] = a[i] + a[j];
                a[j] = a[i] - a[j];
                a[i] = a[i] - a[j];
            }
        }
    }
}

//The coin exchange problem

int minCoinsDP(int money, int *c, int cSize)
{
    std::map<int, int> minCoins;
    minCoins[0] = 0;
    int result = 0;

    for (int i = c[cSize - 1]; i <= money; i++)
    {
        int localMinCoins = 999999999;
        for (int j = 0; j < cSize; j++)
        {
            if (i >= c[j])
            {
                if (localMinCoins > 1 + minCoins.at(i - c[j]))
                {
                    localMinCoins = 1 + minCoins.at(i - c[j]);
                }
            }
        }
        minCoins[i] = localMinCoins;
    }

    return minCoins.at(money);
}

// to help in the main functions
int maxOf2(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int maxOf3(int x, int y, int z)
{
    return maxOf2(maxOf2(x, y), z);
}

int getMistmatchCost(char a, char b);
void outputLCS(int **backtrack, std::string v, int i, int j);
void outputLCS2(int **backtrack, std::string w, int i, int j);
//solving the Manhattan problem
int **manhattanProblem(int n, int m, int **down, int **right, int **diag, std::string v, std::string w)
{
    int s[n + 1][m + 1];
    s[0][0] = 0;

    int **backtrack = new int *[n + 1];

    for (int i = 0; i < n + 1; i++)
    {
        backtrack[i] = new int[m + 1];
    }

    for (int i = 1; i < n + 1; i++)
    {
        s[i][0] = s[i - 1][0] + down[i - 1][0];
    }
    for (int i = 1; i < m + 1; i++)
    {
        s[0][i] = s[0][i - 1] + right[0][i - 1];
    }

    for (int j = 1; j < m + 1; j++)
    {
        for (int i = 1; i < n + 1; i++)
        {
            s[i][j] = maxOf3(s[i - 1][j] + down[i - 1][j], s[i][j - 1] + right[i][j - 1], s[i - 1][j - 1] + getMistmatchCost(v[i - 1], w[j - 1]));

            if (s[i][j] == s[i - 1][j] + down[i - 1][j])
                backtrack[i][j] = -2;
            else if (s[i][j] == s[i][j - 1] + right[i][j - 1])
                backtrack[i][j] = -1;
            else if (s[i][j] + 1 == s[i - 1][j - 1])
                backtrack[i][j] = 0;
        }
    }

    std::cout << s[n][m] << std::endl;

    outputLCS(backtrack, v, n , m );
    std::cout << std::endl;
    outputLCS2(backtrack, w, n , m );

    return backtrack;
}
/* BLOSUM COST:

  4  0 -2 -1 -2  0 -2 -1 -1 -1 -1 -2 -1 -1 -1  1  0  0 -3 -2
  0  9 -3 -4 -2 -3 -3 -1 -3 -1 -1 -3 -3 -3 -3 -1 -1 -1 -2 -2
 -2 -3  6  2 -3 -1 -1 -3 -1 -4 -3  1 -1  0 -2  0 -1 -3 -4 -3
 -1 -4  2  5 -3 -2  0 -3  1 -3 -2  0 -1  2  0  0 -1 -2 -3 -2
 -2 -2 -3 -3  6 -3 -1  0 -3  0  0 -3 -4 -3 -3 -2 -2 -1  1  3
  0 -3 -1 -2 -3  6 -2 -4 -2 -4 -3  0 -2 -2 -2  0 -2 -3 -2 -3
 -2 -3 -1  0 -1 -2  8 -3 -1 -3 -2  1 -2  0  0 -1 -2 -3 -2  2
 -1 -1 -3 -3  0 -4 -3  4 -3  2  1 -3 -3 -3 -3 -2 -1  3 -3 -1
 -1 -3 -1  1 -3 -2 -1 -3  5 -2 -1  0 -1  1  2  0 -1 -2 -3 -2
 -1 -1 -4 -3  0 -4 -3  2 -2  4  2 -3 -3 -2 -2 -2 -1  1 -2 -1
 -1 -1 -3 -2  0 -3 -2  1 -1  2  5 -2 -2  0 -1 -1 -1  1 -1 -1
 -2 -3  1  0 -3  0  1 -3  0 -3 -2  6 -2  0  0  1  0 -3 -4 -2
 -1 -3 -1 -1 -4 -2 -2 -3 -1 -3 -2 -2  7 -1 -2 -1 -1 -2 -4 -3
 -1 -3  0  2 -3 -2  0 -3  1 -2  0  0 -1  5  1  0 -1 -2 -2 -1
 -1 -3 -2  0 -3 -2  0 -3  2 -2 -1  0 -2  1  5 -1 -1 -3 -3 -2
  1 -1  0  0 -2  0 -1 -2  0 -2 -1  1 -1  0 -1  4  1 -2 -3 -2
 0 -1 -1 -1 -2 -2 -2 -1 -1 -1 -1  0 -1 -1 -1  1  5  0 -2 -2
0 -1 -3 -2 -1 -3 -3  3 -2  1  1 -3 -2 -2 -3 -2  0  4 -3 -1
-3 -2 -4 -3  1 -2 -2 -3 -3 -2 -1 -4 -4 -2 -3 -3 -2 -3 11  2
-2 -2 -3 -2  3 -3  2 -1 -2 -1 -1 -2 -3 -1 -2 -2 -2 -1  2  7
*/
int getMistmatchCost(char a, char b)
{

    std::map<char, int> charToIndex;
    charToIndex['A'] = 0;
    charToIndex['C'] = 1;
    charToIndex['D'] = 2;
    charToIndex['E'] = 3;
    charToIndex['F'] = 4;
    charToIndex['G'] = 5;
    charToIndex['H'] = 6;
    charToIndex['I'] = 7;
    charToIndex['K'] = 8;
    charToIndex['L'] = 9;
    charToIndex['M'] = 10;
    charToIndex['N'] = 11;
    charToIndex['P'] = 12;
    charToIndex['Q'] = 13;
    charToIndex['R'] = 14;
    charToIndex['S'] = 15;
    charToIndex['T'] = 16;
    charToIndex['V'] = 17;
    charToIndex['W'] = 18;
    charToIndex['Y'] = 19;

    static bool dataEntered = false;
    static int **diagCost = new int *[20];

    if (!dataEntered)
    {

        for (int i = 0; i < 20; i++)
            diagCost[i] = new int[20];
    }

    if (!dataEntered)
    {

        std::cout << "Enter diagonal cost" << std::endl;
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
                std::cin >> diagCost[i][j];
        }

        dataEntered = true;
    }

    //special character to delete the array from the heap after the program is finished
    if (a == '#')
    {
        for (int i = 0; i < 20; i++)
            delete[] diagCost[i];

        delete[] diagCost;

        return 0;
    }

    return diagCost[charToIndex[a]][charToIndex[b]];
}

//outputs the LCS after solving it by (stringsToMatrx) and (manhattanProblem)
void outputLCS(int **backtrack, std::string v, int i, int j)
{

    if (j < 0 || i < 0)
        return;

    else if (backtrack[i][j] == -2)
    {
        outputLCS(backtrack, v, i - 1, j);
        std::cout << v[i - 1];
    }
    else if (backtrack[i][j] == -1)
    {
        outputLCS(backtrack, v, i, j - 1);
        std::cout << "-";
    }
    else if (backtrack[i][j] == 0)
    {
        outputLCS(backtrack, v, i - 1, j - 1);
        std::cout << v[i - 1];
    }
}

void outputLCS2(int **backtrack, std::string w, int i, int j)
{

    if (j < 0 || i < 0)
        return;

    else if (backtrack[i][j] == -2)
    {
        outputLCS2(backtrack, w, i - 1, j);

        std::cout << "-";
    }
    else if (backtrack[i][j] == -1)
    {
        outputLCS2(backtrack, w, i, j - 1);

        std::cout << w[j - 1];
    }
    else if (backtrack[i][j] == 0)
    {
        outputLCS2(backtrack, w, i - 1, j - 1);
        std::cout << w[j - 1];
    }
}

//transforming two strings to a Manhattan problem
void stringsToMatrix(std::string v, std::string w, int indelCost)
{

    int n = v.length();
    int m = w.length();

    int **down = new int *[n];
    int **right = new int *[n + 1];
    int **diag = new int *[n];

    for (int i = 0; i < n + 1; i++)
    {
        if (i != n)
        {
            down[i] = new int[m + 1];
            diag[i] = new int[m];
        }
        right[i] = new int[m];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            down[i][j] = indelCost;
        }
    }

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            right[i][j] = indelCost;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            diag[i][j] = indelCost;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i] == w[j])
                diag[i][j] = 1;
        }
    }

    manhattanProblem(n, m, down, right, diag, v, w);
}
} // namespace DNAH

#endif // DNAHELP_HPP
