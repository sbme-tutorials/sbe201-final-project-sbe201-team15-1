#include <iostream>
int row = 0;
int column = 0;
int paths(int row, int column, int** down, int** right)
{
    int s1;
    int s2;
    int **s = new int*[row];
    for ( int i = 0; i < row ; i++ )
    {
        s[i] = new int[column];                     
    }
    s[0][0] = 0;
    for(int i = 1; i < row; i++)
    s[i][0] = s[i-1][0] + down[i-1][0];
    for(int j = 1; j < column; j++)
    s[0][j] = s[0][j-1] + right[0][j-1];
    for ( int i = 1; i < row ; i++)
    {
        for ( int j = 1; j < column; j++)
        {
            s1 = s[i-1][j] + down[i-1][j];
            s2 = s[i][j-1] + right[i][j-1];
            if(s1>s2) s[i][j] = s1;
            else s[i][j] = s2;
        }
    }
    return s[row-1][column-1];
}

int main()
{
    std::cout << "Insert number of rows and columns : "<< std::endl;
    std::cin >> row >> column;
    int **right = new int*[row];
    std::cout << " Insert matrix right in rows then columns : " << std::endl;
    for ( int i = 0; i < row ; i++ )
        {
            right[i] = new int[column-1];             
        }
    for ( int i = 0; i < row ; i++)
    {
        for ( int j = 0; j < column-1 ; j++)
        {
            std::cin >> right[i][j];
        }
    }
    int **down = new int*[row-1];
    std::cout << " Insert matrix down in rows then columns : " << std::endl;
    for ( int i = 0; i < row ; i++ )
        {
            down[i] = new int[column];             
        }
    for ( int i = 0; i < row-1 ; i++)
    {
        for ( int j = 0; j < column ; j++)
        {
            std::cin >> down[i][j];
        }
    }
    std::cout<<"right: "<<std::endl;

    for ( int i = 0; i < row ; i++)
    {
        for ( int j = 0; j < column-1 ; j++)
        { 
            std::cout << right[i][j] << " ";           
        }
        std::cout<<std::endl;
    }
    std::cout<<"down: "<<std::endl;
    for ( int i = 0; i < row-1 ; i++)
    {
        for ( int j = 0; j < column ; j++)
        { 
            std::cout << down[i][j] << " ";           
        }
        std::cout<<std::endl;
    }

    int longestPath = paths(row, column, down, right);
    std::cout <<"longest path is " <<longestPath<<std::endl;
    return 0;
}