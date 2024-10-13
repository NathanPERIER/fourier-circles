
#pragma once

#include <optional>
#include <vector>

#include <fmt/format.h>

#include <png.h>

#include "fcircles/utils/colours/rgba.hh"


namespace fcl {

class png_image {

public:
    png_image(size_t width, size_t height, std::optional<rgba> bg_col = std::nullopt);

    // TODO enable moving
    png_image(png_image&&) = delete;
    png_image& operator=(png_image&&) = delete;

    png_image(const png_image&) = delete;
    png_image& operator=(const png_image&) = delete;

    size_t width()  const { return _width;  }
    size_t height() const { return _height; }

    rgba& at(size_t x, size_t y) {
        if(x >= _width) {
            throw std::runtime_error(fmt::format("Cannot get x={} for an image where width={}", x, _width));
        }
        if(y >= _height) {
            throw std::runtime_error(fmt::format("Cannot get y={} for an image where height={}", y, _height));
        }
        return _pixels[_height * y + x];
    }

    const rgba& at(size_t x, size_t y) const {
        if(x >= _width) {
            throw std::runtime_error(fmt::format("Cannot get x={} for an image where width={}", x, _width));
        }
        if(y >= _height) {
            throw std::runtime_error(fmt::format("Cannot get y={} for an image where height={}", y, _height));
        }
        return _pixels[_height * y + x];
    }

    std::vector<uint8_t> dump();

    ~png_image() { png_destroy_write_struct(&_png, &_info); }

private:
    size_t _width;
    size_t _height;

    png_struct* _png  = nullptr;
    png_info*   _info = nullptr;

    std::vector<rgba> _pixels;
};

} // namespace fcl
