
#pragma once

#include <cmath>

#include <npp/math/vec2.hh>


namespace fcl {

class fourier_circle {

public:
    fourier_circle(int64_t speed, double radius): _speed(speed), _radius(radius) {}

    int64_t speed() const { return _speed; }
    double radius() const { return _radius; }

    npp::vec2<npp::R> compute(double t) const {
        const double angle = t * _speed * 2.0 * M_PI;
        return npp::vec2<npp::R>(std::cos(angle), std::sin(angle)) * _radius;
    }

private:
    int64_t _speed;
    double _radius;

};

} // namespace fcl
