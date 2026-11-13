#include "hull.hpp"

std::vector<Pt> graham(std::vector<Pt> P) {
    // 1. remove duplicates; handle n < 3
    // 2. p0 = lowest point
    // 3. sort the rest by angle around p0 using orient() (no atan2!), ties by distance
    // 4. scan with a stack; pop while the last two points and the new one do NOT make a left turn

    std::sort(P.begin(), P.end());
    P.erase(std::unique(P.begin(), P.end()),P.end());
    if (P.size() < 3) {
        return P;
    }

    Pt p0 = P[0];

    std::sort(P.begin() + 1, P.end(), [&](const Pt& a, const Pt& b) {
        long long orientation = orient(p0, a, b);
        if (orientation != 0) {
            return orientation > 0;
        }
        return dist2(p0, a) < dist2(p0, b);
    });

    std::vector<Pt> hull;
    hull.push_back(P[0]);
    hull.push_back(P[1]);
    
    for (size_t i = 2; i < P.size(); i++) {
        while (hull.size() >= 2 && orient(hull[hull.size() - 2], hull.back(), P[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(P[i]);
    }

    return hull;
}

std::vector<Pt> jarvis(std::vector<Pt> P, long long* tests) {
    // start at the lowest point; from the current point choose the candidate such that
    // every other point is to its LEFT (use orient); on ties keep the farthest point

    std::sort(P.begin(), P.end());
    P.erase(std::unique(P.begin(), P.end()), P.end());
    if (P.size() < 3) return P;

    std::vector<Pt> hull;
    Pt start = P[0];
    Pt current = start;

    while(true){
        hull.push_back(current);
        Pt next = (current == P[0]) ? P[1] : P[0];

        for (const Pt& r : P) {
            if (r == current) continue;
            if (tests) ++*tests;

            long long orientation = orient(current, next, r);

            if (orientation < 0) {
                next = r;
            } else if (orientation == 0 && dist2(current, r) > dist2(current, next)) {
                next = r;
            }
        }

        current = next;
        if (current == start) {
            break; 
        }
    }

    return hull;
}
