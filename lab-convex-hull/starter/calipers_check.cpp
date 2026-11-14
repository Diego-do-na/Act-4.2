// Part 5(b): validate rotating calipers (diameter2 in app.cpp) against the O(n^2) brute force,
// then time hull + calipers vs brute force for n = 1e5 points in a square.
// Build (no CGAL needed):  g++ -std=c++17 -O3 calipers_check.cpp hull.cpp -o calipers_check
#define main app_main          // reuse twice_area / perimeter / diameter2 from app.cpp without its main()
#include "app.cpp"
#undef main
#include "gen.hpp"
#include <chrono>

static long long brute_diameter2(const std::vector<Pt>& P) {
    long long best = 0;
    for (size_t i = 0; i < P.size(); i++)
        for (size_t j = i + 1; j < P.size(); j++) best = std::max(best, dist2(P[i], P[j]));
    return best;
}

template <class F> double time_ms(F f) {
    auto t0 = std::chrono::steady_clock::now(); f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

int main() {
    // 1) correctness: 1500 random inputs, half of them with 5 collinear points on the bottom edge
    int bad = 0, total = 0;
    for (unsigned seed = 0; seed < 500; seed++)
        for (std::string d : {"square", "disk", "parabola"}) {
            auto P = gen(d, 1 + seed % 400, seed);
            if (seed % 2) for (long long k = 0; k <= 4; k++) P.push_back({-1000 + 500 * k, -1000000000LL});
            auto H = graham(P);
            Pt a{0, 0}, b{0, 0};
            long long c = diameter2(H, a, b);
            total++;
            if (c != brute_diameter2(P) || dist2(a, b) != c) bad++;
        }
    std::cout << "calipers vs brute force: " << bad << " mismatches out of " << total << "\n";

    // 2) timing for n = 1e5 points in a square
    auto P = gen("square", 100000, 2026);
    std::vector<Pt> H; long long d1 = 0, d2 = 0; Pt a{0, 0}, b{0, 0};
    double t_hull  = time_ms([&] { H = graham(P); });
    double t_cal   = time_ms([&] { d1 = diameter2(H, a, b); });
    double t_brute = time_ms([&] { d2 = brute_diameter2(P); });
    std::cout << "n = 100000 (square), h = " << H.size() << "\n"
              << "  graham hull      : " << t_hull << " ms\n"
              << "  rotating calipers: " << t_cal << " ms\n"
              << "  brute force O(n^2): " << t_brute << " ms\n"
              << "  same diameter    : " << (d1 == d2 ? "yes" : "NO") << "\n";
}
