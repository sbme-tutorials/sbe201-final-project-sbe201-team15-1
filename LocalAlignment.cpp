#include "DNAhelp2.hpp"
#include <iostream>

int main()
{

    std::string s1, s2;
    std::cin >> s1 >> s2;

    DNAH::stringsToMatrix(s1, s2,-5);
}
