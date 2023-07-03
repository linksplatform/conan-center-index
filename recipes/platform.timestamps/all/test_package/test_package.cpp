#include <iostream>
#include <chrono>
#include <Platform.Timestamps.h>

using namespace Platform::Timestamps;

int main() {
    using namespace std::chrono;

    // Test 1
    {
        Timestamp t1(0);
        Timestamp t2(common_era_clock::now());
        if (t1 != t2) {
            std::cout << "Test 1: PASSED" << std::endl;
        } else {
            std::cout << "Test 1: FAILED" << std::endl;
        }
    }

    // Test 2
    {
        auto time1 = std::chrono::system_clock::now();
        Timestamp timestamp1(common_era_clock::from_sys(time1));
        Timestamp timestamp2(timestamp1);
        if (timestamp1 == timestamp2) {
            std::cout << "Test 2: PASSED" << std::endl;
        } else {
            std::cout << "Test 2: FAILED" << std::endl;
        }
    }

    return 0;
}
