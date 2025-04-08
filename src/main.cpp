#include "func.h"

int main() {
    constexpr double dt = 100.0;
    constexpr int steps = 31536000 / dt + 1;
    simulate("../trajectory.csv", dt, steps);
    return 0;
}
