#include "func.h"

int main() {
    constexpr double dt = 160.0;
    constexpr int steps = static_cast<int>((365 * 24 * 60 * 60) / dt) + 100;
    simulate("../trajectory.csv", dt, steps);
    return 0;
}
