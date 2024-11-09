
#pragma once

#include <vector>

#include <npp/math/complex.hh>


namespace fcl {

std::vector<npp::complex> fourier_transform(std::vector<npp::complex> points);

std::vector<npp::complex> inverse_fourier_transform(std::vector<npp::complex> points);

} // namespace fcl
