#include <iostream>

void Nyalia(int a, int b, int c) {
    std::cout << "Actual: ";
    std::cout << a << " | ";
    std::cout << b << " | ";
    std::cout << c << std::endl;
}

int main(void) {

    Nyalia(10, 1000, -30);

    return 0;
};
