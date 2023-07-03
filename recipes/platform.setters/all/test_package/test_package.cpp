#include <iostream>
#include <cassert>
#include <Platform.Setters.h>

using namespace Platform::Setters;

int total_tests = 0;
int passed_tests = 0;

void ParameterlessConstructedSetterTest()
{
    total_tests++;
    auto setter = Setter<std::int32_t>();
    assert(0 == setter.Result());
    passed_tests++;
}

void ConstructedWithDefaultValueSetterTest()
{
    total_tests++;
    auto setter = Setter<std::int32_t>(9);
    assert(9 == setter.Result());
    passed_tests++;
}

void MethodsWithBooleanReturnTypeTest()
{
    total_tests++;
    auto setter = Setter<std::int32_t>();
    assert(true == setter.SetAndReturnTrue(1));
    assert(1 == setter.Result());
    assert(false == setter.SetAndReturnFalse(2));
    assert(2 == setter.Result());
    auto array3 = std::to_array<std::int32_t>({3});
    assert(true == setter.SetFirstAndReturnTrue(array3));
    assert(3 == setter.Result());
    auto array4 = std::to_array<std::int32_t>({4});
    assert(false == setter.SetFirstAndReturnFalse(array4));
    assert(4 == setter.Result());
    passed_tests++;
}

void MethodsWithIntegerReturnTypeTest()
{
    total_tests++;
    auto setter = Setter<std::int32_t, std::int32_t>(1, 0);
    assert(1 == setter.SetAndReturnTrue(1));
    assert(1 == setter.Result());
    assert(0 == setter.SetAndReturnFalse(2));
    assert(2 == setter.Result());
    auto array3 = std::to_array<std::int32_t>({3});
    assert(1 == setter.SetFirstAndReturnTrue(array3));
    assert(3 == setter.Result());
    auto array4 = std::to_array<std::int32_t>({4});
    assert(0 == setter.SetFirstAndReturnFalse(array4));
    assert(4 == setter.Result());
    passed_tests++;
}

int main()
{
    ParameterlessConstructedSetterTest();
    ConstructedWithDefaultValueSetterTest();
    MethodsWithBooleanReturnTypeTest();
    MethodsWithIntegerReturnTypeTest();

    std::cout << "Total tests: " << total_tests << std::endl;
    std::cout << "Passed tests: " << passed_tests << std::endl;

    return 0;
}
