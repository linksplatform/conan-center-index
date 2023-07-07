#include <iostream>
#include <cstdint>
#include <Platform.Data.Doublets.h>

int main()
{  
    using namespace Platform::Memory;
    using namespace Platform::Data::Doublets::Memory::United::Generic;
    using namespace Platform::Data::Doublets;
    HeapResizableDirectMemory memory {};
    UnitedMemoryLinks<LinksOptions<std::uint64_t>, HeapResizableDirectMemory> storage {std::move(memory)};
    auto link = Create(storage);
    auto count = Count(storage);
    if(link == 1 && count == 1) {
        std::cout << "Test: Success" << std::endl;
    }
    else {
        std::cout << "Test: Failed" << std::endl;
    }
    return 0;
}

