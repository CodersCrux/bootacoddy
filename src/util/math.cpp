#include "math.hpp"

namespace bac::math {

    i32 abs(i32 num) { return num < 0 ? -num : num; }

    i32 pow(i32 num, i32 power) {

        i32 res = 1;
        if (power < 0)
            return 0;
        if (power == 0)
            return 1;
        while (power--)
            res *= num;
        return res;
    }

    u32 max(u32 a, u32 b) {
        return a > b ? a : b;
    }

    u32 min(u32 a, u32 b) {
        return a < b ? a : b;
    }

}
