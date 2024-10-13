#include "fcircles/draw/circle.hh"

#include <cmath>


namespace {

/// @param v vector from the centre of the disc to a point
/// @param radius the external radius of the disc
/// @return wheter or not the point is in the disc
bool check_point_out_of_disc(npp::vec2<npp::N> v, size_t radius) {
    // Assume x >= 0, y >= 0, r >= 1
    // Basically, check if the distance between the current pixel (x, y) and the centre of the disc (0, 0) is greater than the radius r
    // i.e. sqrt(x² + (y+0.5)²) >= r     (with offset correction on y, because we are working with pixels)
    //   => x² + (y + 0.5)² >= r²        (the square function is strictly increasing on [1, +inf[)
    //  <=> x² + y² + 2 * 0.5 * y + 0.5 * 0.5 >= r²
    //  <=> x² + y² + y + 0.25 >= r²
    //   => x² + y(y + 1) >= r²          (because we only want to work with integers)
    if (radius == 0) [[unlikely]] {
        return false;
    }
    // const double yc = static_cast<double>(v.y) + 0.5;
    // return (static_cast<double>(v.x * v.x) + (yc * yc)) >= static_cast<double>(radius * radius);
    return static_cast<uint64_t>(v.x * v.x + v.y * (v.y + 1)) >= (radius * radius);
}

} // anonymous namespace


namespace fcl {

std::vector<npp::vec2<npp::N>> compute_circle_points(size_t radius) {
    std::vector<npp::vec2<npp::N>> res;
    if(radius == 0) {
        res.push_back(npp::vec2<npp::N>::zero());
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
    npp::vec2<npp::N> current(0, radius);
    while(current.x <= current.y) {
        res.push_back(current);
        current.x += 1;
        if(::check_point_out_of_disc(current, radius + 1)) {
            current.y -= 1;
        }
    }

    // Then, we just have to flip the first octant to get a quarter circle
    // Caution has to be taken not to duplicate a point if a circle intersects with the x=y diagonal
    res.reserve(res.size() * 2);
    const size_t octant_end_idx = res.size() - ((std::abs(res.back().x - res.back().y) >= 1) ? 1 : 2);
    for(int64_t i = static_cast<int64_t>(octant_end_idx); i >= 0; i--) {
        res.push_back(npp::vec2<npp::N>(res[i].y, res[i].x));
    }

    // Next step is to mirror the quadrant we have below the y axis
    // Note that we do not mirror the last point (x=r, y=0) since it has already been included
    res.reserve(res.size() * 4);
    for(int64_t i = static_cast<int64_t>(res.size() - 2); i >= 0; i--) {
        res.push_back(npp::vec2<npp::N>(res[i].x, -1 * res[i].y));
    }

    // Finally, we mirror the half we have on the other side of the x axis
    for(size_t i = res.size() - 2; i >= 1; i--) {
        res.push_back(npp::vec2<npp::N>(-1 * res[i].x, res[i].y));
    }

    return res;
}

} // namespace fcl
