
#pragma once

#include <limits>
#include <vector>

#include <npp/math/complex.hh>

#include "fcircles/draw/png_image.hh"


namespace fcl::detail {

class minmax {

public:
    minmax() {}

    void add(double val) {
        if(val > _max) {
            _max = val;
        }
        if(val < _min) {
            _min = val;
        }
    }

    double min() const { return _min; }
    double max() const { return _max; }

    double width() const { return _max - _min; }

private:
    double _min = std::numeric_limits<double>::infinity();
    double _max = -1 * std::numeric_limits<double>::infinity();

};

} // namespace fcl::detail


namespace fcl {

class canvas {

public:
    canvas() {};

    void add(double x, double y);
    void add(npp::complex c) { add(c.re(), c.im()); }

    png_image draw();

private:
    std::vector<npp::vec2<npp::N>> _points;

    fcl::detail::minmax _x_bounds;
    fcl::detail::minmax _y_bounds;
};

} // namespace fcl
