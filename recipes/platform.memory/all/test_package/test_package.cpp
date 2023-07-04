#include <iostream>
#include <Platform.Memory.h>

namespace Platform::Memory::Tests
{
    std::byte GetLastByte(const HeapResizableDirectMemory& heapMemory)
    {
        auto pointer1 = heapMemory.Pointer();
        return *((std::byte*)pointer1 + heapMemory.ReservedCapacity() - 1);
    }

    std::byte GetLastByteByCopy(HeapResizableDirectMemory heapMemory)
    {
        auto pointer1 = heapMemory.Pointer();
        return *((std::byte*)pointer1 + heapMemory.ReservedCapacity() - 1);
    }

    void TestHeapResizableDirectMemory()
    {
        auto heapMemory = HeapResizableDirectMemory();
        auto value1 = GetLastByte(heapMemory);
        heapMemory.ReservedCapacity(heapMemory.ReservedCapacity() * 2);
        auto value2 = GetLastByteByCopy(heapMemory);

        if (value1 != value2) 
        {
            std::cout << "TestHeapResizableDirectMemory: FAILURE: Expected value1 to equal value2\n";
            return;
        }

        if (value1 != std::byte{0})
        {
            std::cout << "TestHeapResizableDirectMemory: FAILURE: Expected value1 to be std::byte{0}\n";
            return;
        }

        if (&value1 == &value2)
        {
            std::cout << "TestHeapResizableDirectMemory: FAILURE: Expected value1 and value2 to have different addresses\n";
            return;
        }

        std::cout << "TestHeapResizableDirectMemory: SUCCESS\n";
    }
}

int main()
{
    Platform::Memory::Tests::TestHeapResizableDirectMemory();
    return 0;
}
