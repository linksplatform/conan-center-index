#include <iostream>
#include <array>
#include <Platform.Collections.h>

using namespace Platform::Collections;

void RunGetElementTest()
{
    auto nullArray = std::array<int, 0>{};
    int element;

    // Test GetElementOrDefault for nullArray
    element = Arrays::GetElementOrDefault(nullArray, 1);
    std::cout << "GetElementOrDefault(nullArray, 1): " << element << std::endl;

    // Test TryGetElement for nullArray
    bool result = Arrays::TryGetElement(nullArray, 1, element);
    std::cout << "TryGetElement(nullArray, 1, element): " << (result ? "true" : "false") << std::endl;
    std::cout << "Element value: " << element << std::endl;

    auto array = std::array{1, 2, 3};

    // Test GetElementOrDefault for array
    element = Arrays::GetElementOrDefault(array, 2);
    std::cout << "GetElementOrDefault(array, 2): " << element << std::endl;

    // Test TryGetElement for array
    result = Arrays::TryGetElement(array, 2, element);
    std::cout << "TryGetElement(array, 2, element): " << (result ? "true" : "false") << std::endl;
    std::cout << "Element value: " << element << std::endl;

    // Test GetElementOrDefault for out-of-range index
    element = Arrays::GetElementOrDefault(array, 10);
    std::cout << "GetElementOrDefault(array, 10): " << element << std::endl;

    // Test TryGetElement for out-of-range index
    result = Arrays::TryGetElement(array, 10, element);
    std::cout << "TryGetElement(array, 10, element): " << (result ? "true" : "false") << std::endl;
    std::cout << "Element value: " << element << std::endl;
}

int main()
{
    RunGetElementTest();
    return 0;
}