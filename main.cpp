#include <iostream>

float getNum(float a);

int main(int argc, char const *argv[])
{
    int a = 20;
    float b;

    b = getNum(a);
    std::cout << a << std::endl;
    
    return 0;
}


float getNum(float b){
    return b;
}