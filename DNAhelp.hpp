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

//solving the Manhattan problem
int **manhattanProblem(int n, int m, int **down, int **right, int **diag)
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
            s[i][j] = maxOf3(s[i - 1][j] + down[i - 1][j], s[i][j - 1] + right[i][j - 1], s[i - 1][j - 1] + diag[i - 1][j - 1]);

            if (s[i][j] == s[i - 1][j])
                backtrack[i][j] = -2;
            else if (s[i][j] == s[i][j - 1])
                backtrack[i][j] = -1;
            else if (s[i][j] + 1 == s[i - 1][j - 1])
                backtrack[i][j] = 0;
        }
    }

    return backtrack;
}

//outputs the LCS after solving it by (stringsToMatrx) and (manhattanProblem)
void outputLCS(int **backtrack, std::string v, int i, int j)
{

    if (j == 0 || i == 0)
        return;

    else if (backtrack[i][j] == -2)
        outputLCS(backtrack, v, i - 1, j);
    else if (backtrack[i][j] == -1)
        outputLCS(backtrack, v, i, j - 1);
    else if (backtrack[i][j] == 0)
    {
        outputLCS(backtrack, v, i - 1, j - 1);
        std::cout << v[i - 1];
    }
}

//transforming two strings to a Manhattan problem
void stringsToMatrix(std::string v, std::string w)
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
            down[i][j] = 0;
        }
    }

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            right[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            diag[i][j] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i] == w[j])
                diag[i][j] = 1;
        }
    }

    outputLCS(manhattanProblem(n, m, down, right, diag), v, n, m);
}
} // namespace DNAH

#endif // DNAHELP_HPP