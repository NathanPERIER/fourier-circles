#include "fcircles/draw/circle.hh"

#include <cmath>

#include <fmt/format.h>


namespace {

double vec_length(npp::vec2<npp::R> v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

} // anonymous namespace


namespace fcl {

std::vector<npp::vec2<npp::R>> compute_circle_points(double radius) {
    std::vector<npp::vec2<npp::R>> res;
    if(radius == 0) {
        res.push_back(npp::vec2<npp::R>::zero());
        return res;
    }

    // We start drawing the circle clockwise at (x=0, y=r)
    // The first quadrant ends at (x=r, y=0)
    // The end of the first octant is around the x=y diagonal, there are two possible cases :
    // 
    //   y  OOO   /    |   OO    /
    //   ^     OO/     |     OO / 
    //          /O     |       O  
    //         / O     |      / O 
    //        /   O    |     /  O 
    //            O    |         O  >x
    //
    // Basically, we know we have reached the second octant when x > y
    npp::vec2<npp::R> current(0, radius);
    while(current.x <= current.y) {
        res.push_back(current);
        current.x += 1;
        if((::vec_length(current + npp::vec2<npp::R>(0, 0.5)) - radius) > 1) {
            current.y -= 1;
        }
    }

    // Then, we just have to flip the first octant to get a quarter circle
    // Caution has to be taken not to duplicate a point if a circle intersects with the x=y diagonal
    res.reserve(res.size() * 2);
    const size_t octant_end_idx = res.size() - ((std::abs(res.back().x - res.back().y) >= 1) ? 1 : 2);
    for(int64_t i = static_cast<int64_t>(octant_end_idx); i >= 0; i--) {
        res.push_back(npp::vec2<npp::R>(res[i].y, res[i].x));
    }

    // Next step is to mirror the quadrant we have below the y axis
    // Note that we do not mirror the last point (x=r, y=0) since it has already been included
    res.reserve(res.size() * 4);
    for(int64_t i = static_cast<int64_t>(res.size() - 2); i >= 0; i--) {
        res.push_back(npp::vec2<npp::R>(res[i].x, -1 * res[i].y));
    }

    // Finally, we mirror the half we have on the other side of the x axis
    for(size_t i = res.size() - 2; i >= 1; i--) {
        res.push_back(npp::vec2<npp::R>(-1 * res[i].x, res[i].y));
    }

    return res;
}

} // namespace fcl
