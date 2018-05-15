#include <iostream>
#include <stdlib.h>
#include <stdio.h>
long unsigned int row;
long unsigned int column;
char** backtrack( std::string v, std::string w, long unsigned int row, long unsigned int column )
{
    int match;
    char** back = new char*[row+1];
    for ( int i = 0; i < row+1; i++ )
    {
        back[i] = new char[column+1];             
    }
    back[0][0] = '.';
    int s1;
    int s2;
    int s3;
    int **s = new int*[row+1];
    for ( int i = 0; i < row+1 ; i++ )
    {
        s[i] = new int[column+1];                     
    }
    s[0][0] = 0;
    for(int i = 1; i < row+1; i++)
    {
        s[i][0] = 0;
        back[i][0] = '|';
    }
    for(int j = 1; j < column+1; j++)
    {
        s[0][j] = 0;
        back[0][j] = '>';
    }
    for ( int i = 1; i <= row ; i++)
    {
        for ( int j = 1; j <= column; j++)
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
            //std::cout<<"backtrack ";
        }
        //std::cout<<"backtrack ";
    }
    //std::cout<<""<<std::endl;
    return back;
}

void LCS( char** back, std::string v, int i, int j, std::string &largComSeq )
{
    if( i == 0 || j == 0 ) 
    {
        //std::cout<<"lgsEnd "<<std::endl; 
        return;
    }
    if( back[i][j] == '>' )
    LCS( back, v, i, j-1, largComSeq );
    else if( back[i][j] == '|' )
    LCS( back, v, i-1, j, largComSeq );
    else 
    {
        LCS( back, v, i-1, j-1, largComSeq );
        largComSeq.push_back(v[i]);
    }
    //std::cout<<"lgs ";
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
    //std::cout<<row<<"x"<<column<<std::endl;
    char** back = new char*[row+1];
    for ( int i = 0; i < row+1 ; i++ )
    {
        back[i] = new char[column+1];             
    }
    back = backtrack( v, w, row, column );
    /*for ( int i = 0; i < row+1 ; i++)
    {
        for ( int j = 0; j < column+1 ; j++)
        { 
            std::cout << back[i][j] << " "; 
                     
        }
        std::cout<<std::endl;
    }*/
    std::string largCommSeq;
    LCS( back, v, row-1, column-1, largCommSeq );
    std::cout<<"Largest common sequence is "<<std::endl;
    /*for( int i = 0; i < row; i++ )
    {
        std::cout<<largCommSeq[i];
    }
    std::cout<<""<<std::endl;*/
    std::cout<<largCommSeq<<std::endl;

    return 0;
}