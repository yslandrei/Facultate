#include <iostream>
#include "LO.h"
#include "Iterator.h"
#include "TestScurt.h"
#include "TestExtins.h"

bool rel(TElement a, TElement b) {
    return a < b;
}

int main() {
    testAll();
    testAllExtins();
    std::cout << "Finished LI Tests!" << std::endl;
}