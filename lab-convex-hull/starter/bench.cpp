// Part 4: timing experiments. Prints CSV: dist,n,h,algo,ms,tests
#include "hull.hpp"
#include "gen.hpp"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_graham_andrew.h>
#include <CGAL/ch_jarvis.h>
#include <chrono>
#include <iostream>
using K  = CGAL::Exact_predicates_inexact_constructions_kernel;
using P2 = K::Point_2;

template <class F> double time_ms(F f) {
    auto t0 = std::chrono::steady_clock::now(); f();
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

int main() {
    std::cout << "dist,n,h,algo,ms,tests\n";
    for (std::string d : {"square", "disk", "parabola"})
        for (int n : {1000, 3000, 10000, 30000, 100000, 300000, 1000000}) {
            if (d == "parabola" && n > 60000) continue;
            auto P = gen(d, n, 2026);
            std::vector<P2> in;
            for (auto& p : P) in.emplace_back((double)p.x, (double)p.y);
            size_t h = 0;
            double t = time_ms([&] { h = graham(P).size(); });
            std::cout << d << "," << n << "," << h << ",graham," << t << ",\n";
            // TODO: time your jarvis (print the number of orientation tests too).
            //       Skip it when n*h is so large that it would take more than a few seconds.
            // TODO: time CGAL::convex_hull_2, CGAL::ch_graham_andrew and CGAL::ch_jarvis
            //       (use std::back_inserter into a std::vector<P2>).
        }
}
