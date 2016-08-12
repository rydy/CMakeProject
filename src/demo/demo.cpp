#include <iostream>
#include "demo_lib.h"
#include "demo_dll.h"

int main()
{
	std::cout << "CamkeProject" << std::endl;
	std::cout << FunC(1, 2) << std::endl;
	std::cout << Func(1, 2) << std::endl;
	return 0;
}