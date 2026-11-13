// Usage: ./hull graham < data/example13.txt     (or: ./hull jarvis)
// Input : n, then n lines "x y" (integers).  Output: h, then the h hull vertices.
#include "hull.hpp"
#include <iostream>
#include <string>
int main(int argc, char** argv) {
    std::string algo = argc > 1 ? argv[1] : "graham";
    int n; std::cin >> n;
    std::vector<Pt> P(n);
    for (auto& p : P) std::cin >> p.x >> p.y;
    auto H = (algo == "jarvis") ? jarvis(P) : graham(P);
    std::cout << H.size() << "\n";
    for (auto& p : H) std::cout << p.x << " " << p.y << "\n";
}
