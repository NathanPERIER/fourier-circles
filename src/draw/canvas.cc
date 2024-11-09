#include "fcircles/draw/canvas.hh"


namespace fcl {

void canvas::add(double x, double y) {
    _points.emplace_back(static_cast<int64_t>(x), static_cast<int64_t>(y));
    _x_bounds.add(x);
    _y_bounds.add(y);
}

png_image canvas::draw() {
    detail::minmax x_bounds = _x_bounds;
    detail::minmax y_bounds = _y_bounds;
    x_bounds.add(0);
    y_bounds.add(0);

    const npp::vec2<npp::N> offset(1 - x_bounds.min(), 1 - y_bounds.min());

    png_image img(x_bounds.max() - x_bounds.min() + 3, y_bounds.max() - y_bounds.min() + 3, npp::rgba{ .r = 255, .g = 255, .b = 255, .a = 255 });

    const npp::rgba fg_col { .r = 255, .g = 0, .b = 0, .a = 128 };
    const npp::rgba origin_col { .r = 0, .g = 0, .b = 255, .a = 128 };

    for(const npp::vec2<npp::N>& p: _points) {
        npp::vec2<npp::N> centred = p + offset;
        img.at(centred.x, centred.y) = fg_col;
    }
    img.at(offset.x, offset.y) = origin_col;

    return img;
}

} // namespace fcl
