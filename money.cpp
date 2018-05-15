#include <iostream>

int minChange( int* minCoinsList, int &money )
{
    bool oddNo = true;
    int smallest[10000000];
    int minimumOfCoins;
    if( money == 0 ) return 0;
    
    int bound;
    for( int i = 2; i <= money; i++ )
    {
        if( minCoinsList[i] == 1 )
        {
            i++;
        }
        
        if( i%2 == 0 )
        {
            bound = i/2;
            minimumOfCoins = 2*minCoinsList[bound];
            oddNo = false;
        }  
        else
        {
            oddNo = true;
            bound = (i-1)/2;
        }          
        for( int j = 1; j <= bound; j++)
        {
            smallest[j] = minCoinsList[i-j] + minCoinsList[j];
            if( j==1 && oddNo )
            {
                minimumOfCoins=smallest[j]; 
            }
            else if( smallest[j] < minimumOfCoins )
            {
                minimumOfCoins = smallest[j];
            }                            
        }
            minCoinsList[i] = minimumOfCoins;        
    }
    return minCoinsList[money];

}


int main()
{
    int size = 0;
    int money1 = 0;
    std::cout<< "Enter money "<<std::endl;
    std::cin>>money1;
    std::cout<< "Enter number of denominations "<<std::endl;
    std::cin>>size;
    int* minCoins = nullptr;
    minCoins = new int[2*money1];
    int* coins = nullptr;
    coins = new int [size];
    std::cout<< "Enter denominations "<<std::endl;
    for( int i = 0; i < size; i++ )
    {
        std::cin>>coins[i];
        minCoins[coins[i]] = 1;
    } 
    
    minCoins[0] = 0;
    int minimumChange = minChange(&minCoins[0], money1);
    std::cout<<"Minimum number of coins is "<<minimumChange<<std::endl;

    delete [] minCoins;
    minCoins = nullptr;
    delete [] coins;
    coins = nullptr;
    return 0;
}
