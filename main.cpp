#include <iostream>
#include <vector>
#include <cstdint>

#include <tracy/Tracy.hpp>

struct SimulateWork {
    SimulateWork()
        : bytes_(0x1000, 0)
    {}

    void frame() {
        ZoneScoped;
        subtask_1();
        subtask_2();
        subtask_3();
    }

private:
    std::vector<uint8_t> bytes_;

    void subtask_1() {
        ZoneScoped;
        for (size_t i = 0; i < bytes_.size(); i++) {
            bytes_[i] *= 1 + (bytes_[i] % 12);
        }
    }

    void subtask_2() {
        ZoneScoped;
        for (size_t i = 0; i < bytes_.size()-1; i++) {
            bytes_[i] += bytes_[i+1];
            bytes_[i] %= 243;
        }
    }

    void subtask_3() {
        ZoneScoped;
        for (size_t i = 0; i < bytes_.size()-1; i++) {
            for (size_t j = 0; j < i; j++) {
                bytes_[i] += bytes_[j];
                bytes_[i] %= 253;
            }
        }
    }
};

int main() {
    SimulateWork work;

    for (size_t i = 0; i < 100'000; i++) {
        FrameMark;
        work.frame();
    }

    return 0;
}
