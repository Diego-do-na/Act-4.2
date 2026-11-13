#include "hull.hpp"

std::vector<Pt> graham(std::vector<Pt> P) {
    // 1. remove duplicates; handle n < 3
    // 2. p0 = lowest point
    // 3. sort the rest by angle around p0 using orient() (no atan2!), ties by distance
    // 4. scan with a stack; pop while the last two points and the new one do NOT make a left turn
    return {}; // TODO
}

std::vector<Pt> jarvis(std::vector<Pt> P, long long* tests) {
    // start at the lowest point; from the current point choose the candidate such that
    // every other point is to its LEFT (use orient); on ties keep the farthest point
    return {}; // TODO
}
