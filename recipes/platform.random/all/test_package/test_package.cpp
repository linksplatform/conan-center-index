#include <Platform.Random.h>
#include <iostream>

using namespace Platform::Random;

int main()
{

    std::uint64_t lastValue = 0;
    int theSameCount = 0;

    for (int i = 0; i < 10; i++)
    {
        std::uint64_t newValue = NextUInt64(RandomHelpers::Default);
        if (newValue == lastValue)
        {
            theSameCount++;
        }
        else
        {
            lastValue = newValue;
            theSameCount = 0;
        }

        std::uint64_t temp = NextUInt64(RandomHelpers::Default, {0UL, 5UL});
        std::cout << "Generated value: " << temp << std::endl;
        if (temp <= 5UL && temp >= 0UL)
        {
            std::cout << "Value is within the expected range." << std::endl;
        }
        else
        {
            std::cout << "Value is outside the expected range." << std::endl;
        }
    }
    std::cout << "The same count: " << theSameCount << std::endl;
    
    int trueCount = 0;
    int falseCount = 0;
    
    for (int i = 0; i < 10; i++)
    {
        bool newValue = NextBoolean(RandomHelpers::Default);
        if (newValue)
        {
            trueCount++;
        }
        else
        {
            falseCount++;
        }
    }
    
    std::cout << "True count: " << trueCount << std::endl;
    std::cout << "False count: " << falseCount << std::endl;
    
    return 0;
}