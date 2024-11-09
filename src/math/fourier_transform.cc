#include "fcircles/math/fourier_transform.hh"


namespace fcl {

std::vector<npp::complex> fourier_transform(std::vector<npp::complex> points) {
    std::vector<npp::complex> res;
    for(uint64_t k = 0; k < points.size(); k++) {
        npp::complex x = 0;
        for(uint64_t n = 0; n < points.size(); n++) {
            x += points[n] * npp::complex::polar(1, -2.0 * M_PI * static_cast<double>(k) * static_cast<double>(n) / static_cast<double>(points.size()));
        }
        res.push_back(x);
    }
    return res;
}

std::vector<npp::complex> inverse_fourier_transform(std::vector<npp::complex> points) {
    std::vector<npp::complex> res;
    for(uint64_t n = 0; n < points.size(); n++) {
        npp::complex x = 0;
        for(uint64_t k = 0; k < points.size(); k++) {
            x += points[k] * npp::complex::polar(1, 2.0 * M_PI * static_cast<double>(k) * static_cast<double>(n) / static_cast<double>(points.size()));
        }
        res.push_back(x / static_cast<double>(points.size()));
    }
    return res;
}

} // namespace fcl
