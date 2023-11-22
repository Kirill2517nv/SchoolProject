#include <iostream>
#include <memory>
#include <Application.hpp>
#include <vector>
#include <algorithm>
#include <Interface.hpp>



int main()
{
	srand(time(0));
	auto pEditor = std::make_shared<Interface>();
	int returnCode = pEditor->start();
	return returnCode;
}