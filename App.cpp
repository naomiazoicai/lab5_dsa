#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testAllExtended();
    testEquality();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}

