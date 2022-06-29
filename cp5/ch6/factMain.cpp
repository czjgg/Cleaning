#include "Chapter6.h"
#include <iostream>

void print(const int (&ia)[10])
{
	for (size_t i = 0; i != 10; ++i)
		std::cout << ia[i] << std::endl;
}
int main()
{
    // std::cout << "5! is " << fact(5) << std::endl;
    // std::cout << func() << std::endl;
    // std::cout << abs(-9.78) << std::endl;
    int ia[10]{1,2,3,4,5,6,7,8,9,0};
    print(ia);
    getchar();
}