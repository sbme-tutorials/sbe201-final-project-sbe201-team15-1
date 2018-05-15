#include <map>
#include <string>
#include <cmath>
#include <iostream> 

int minOf2 (int x, int y)
{
    if (x > y)
        return y;
    else
        return x;
}

/*
int** subAllignement (char **seq1 , char **seq2 )
{
 if you found identical segment in the two sub sequences 
 get the difference of the first element index in the first sequence and the first element index in the second sequence 
 insert "-" before the first element in the delayed sequence  //repeat with the difference you calculated
 insert the same number of "-" at the end of the advanced sequence 
 you got alligned sub sequence
 return two alligned subsequences 
}

void basicAllignment (char **seq1 , char **seq2 , int seq1Size , int seq2Size)
{
    int s = minOf2(seq1Size,seq2Size) ;
    int saveIndex[] ;
    for (int i=0 ; i<s ; i++)
    {
        if (seq1[i] = seq2[i])
        insert in saveIndex[] the value of i 
    }  
    now you got the number of sub sequences 

       new LL1 = seq1 till saveIndex[0]    //    
       new ll2 = seq2 till saveIndex[0]    //     repeat these three steps with size of saveIndex
       subAllignement(ll1 , ll2)           //
    merge returned subsequences    
}
*/

int maxOf2(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int ManhattanTourist(int n, int m, int **Right, int **Down)  //need to check
{
    /*if(n=0)
    return maxOf2 (Right[0][0] , Down[0],[0]) ;*/
    if(n=-1 || m=-1)
    return maxOf2 (Right[0][0] , Down[0],[0]) ;
    int max = maxOf2(Down[n][m+1] ,Right[n+1][m]); 
    return max + maxOf2( ManhattanTourist (n , m-1 , Down ,Right ) , ManhattanTourist (n-1 , m , Down ,Right )  ) ;
}


int minCoins (int money , int *d , int dsize)   //need a very tiny edit
{
    int remain[dsize] ;
    int dv[dsize] ;
    int lastOne[dsize] ;
    int minvalue=9999999 ;
    for (int i=0 ; i<dsize ; i++)
    {
        dv[i] = money / d[i] ;
        remain[i]= money % d[i] ;
    }
    for (int h=0 ; h< dsize ; h++)
    {   
        if ( remain[h] > d[h+1] )
        {
            remain[h] = remain[h] % d[h+1] ;
        }   

    }
        for (int j=0 ; j<dsize ; j++)
        {    
            lastOne[j] = dv[j] + remain[j] ;
            if (minvalue > lastOne[j])
                minvalue=lastOne[j] ;      
            }
    return minvalue ; 
}

