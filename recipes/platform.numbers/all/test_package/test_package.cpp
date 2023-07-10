#include <iostream>
#include <cassert>
#include <cstdint>
#include <limits>
#include <Platform.Numbers.h>

namespace Platform::Numbers::Tests
{
    void GetLowestBitPositionTest()
    {
        std::uint64_t value = 32;
        std::int32_t expectedPosition = 5;
        assert(Platform::Numbers::Bit::GetLowestPosition(value) == expectedPosition);
        std::cout << "GetLowestBitPositionTest passed" << std::endl;
    }

    void PartialReadWriteTest()
    {
        std::uint32_t firstValue = 1;
        std::uint32_t secondValue = 1543;
        std::uint32_t value = Platform::Numbers::Bit::PartialWrite<std::uint32_t>(secondValue, firstValue, 0, 1);
        std::uint32_t readValue = Platform::Numbers::Bit::PartialRead<std::uint32_t>(value, 0, 1);
        assert(readValue == firstValue);
        std::cout << "PartialReadWriteTest passed" << std::endl;
    }
}

int main()
{
    Platform::Numbers::Tests::GetLowestBitPositionTest();
    Platform::Numbers::Tests::PartialReadWriteTest();

    return 0;
}
