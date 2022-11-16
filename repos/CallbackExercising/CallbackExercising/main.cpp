
#include <iostream>


void Printer(int (*NumberFunc)(void))
{
	std::cout << NumberFunc();
}


int num1()
{
	return 40;
}

int num2()
{
	return 50;
}


int main()
{

	
	Printer(&num1);



	return 0;
}