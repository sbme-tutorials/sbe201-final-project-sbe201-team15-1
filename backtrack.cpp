#include <iostream>
#include <stdlib.h>
#include <stdio.h>
long unsigned int row;
long unsigned int column;
char** backtrack( std::string v, std::string w, long unsigned int row, long unsigned int column )
{
    int match;
    char** back = new char*[row+1];
    for ( int i = 0; i < row+1 ; i++ )
    {
        back[i] = new char[column+1];             
    }
    back[0][0] = '.';
    int s1;
    int s2;
    int s3;
    int **s = new int*[row];
    for ( int i = 0; i < row ; i++ )
    {
        s[i] = new int[column];                     
    }
    for(int i = 0; i < row; i++)
    {
        s[i][0] = 0;
        back[i+1][0] = '|';
    }
    for(int j = 0; j < column; j++)
    {
        s[0][j] = 0;
        back[0][j+1] = '>';
    }
    for ( int i = 1; i < row ; i++)
    {
        for ( int j = 1; j < column; j++)
        {
            if( v[i-1] == w[j-1] )
            {
                match = 1;
            }
            else
            {
                match = 0;
            }
            s1 = s[i-1][j];
            s2 = s[i][j-1];
            s3 = s[i-1][j-1] + match;
            if( s1 > s2 && s1 > s3) 
            {
                s[i][j] = s1;
            }
            else if( s2 > s1 && s2 > s3) 
            {
                s[i][j] = s2;
            }
            else
            {
                s[i][j] = s3;
            }
            if( s[i][j] == s1 )
            {
                back[i][j] = '|';
            }
            else if( s[i][j] == s2 )
            {
                back[i][j] = '>';
            }
            else 
            {
                back[i][j] = '/';
            } 
        }
    }

    return back;
}

void LCS( char** back, std::string v, int i, int j, std::string &largComSeq )
{
    if( i == 0 || j == 0 ) return;
    else if( back[i][j] == '>' )
    LCS( back, v, i, j-1, largComSeq );
    else if( back[i][j] == '|' )
    LCS( back, v, i-1, j, largComSeq );
    else 
    LCS( back, v, i-1, j-1, largComSeq );
    largComSeq[i] = v[i];
}

int main()
{
    std::string v;
    std::string w;
    std::cout << "Insert vertical sequence : "<< std::endl;
    std::cin>>v;
    std::cout << "Insert horizontal sequence : "<< std::endl;
    std::cin>>w;
    row = v.length();
    column = w.length();
    char** back = new char*[row+1];
    for ( int i = 0; i < row+1 ; i++ )
    {
        back[i] = new char[column+1];             
    }
    back = backtrack( v, w, row, column );
    std::string largCommSeq;
    LCS( back, v, row, column, largCommSeq );
    std::cout<<"Largest common sequence is "<<std::endl;
    for( int i = 0; i < row+1; i++ )
    {
        std::cout<<largCommSeq[i];
    }
    //std::cout<<largCommSeq;
    std::cout<<""<<std::endl;

    return 0;
}