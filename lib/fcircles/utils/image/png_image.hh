
#pragma once

#include <optional>
#include <vector>

#include <fmt/format.h>

#include <png.h>

#include <npp/colour/rgba.hh>


namespace fcl::detail {

class png_data_holder {

public:
    png_data_holder() {};

    png_data_holder(png_data_holder&& holder): _png(holder._png), _info(holder._info) {
        holder._png = nullptr;
        holder._info = nullptr;
    };

    png_data_holder& operator=(png_data_holder&& holder) {
        destroy();
        _png = holder._png;
        _info = holder._info;
        holder._png = nullptr;
        holder._info = nullptr;
        return *this;
    }

    png_data_holder(const png_data_holder&) = delete;
    png_data_holder& operator=(const png_data_holder&) = delete;

    void init();

    png_struct* png() { return _png; }
    png_info* info() { return _info; }

    ~png_data_holder() { destroy(); }

private:
    png_struct* _png  = nullptr;
    png_info*   _info = nullptr;

    void destroy() {
        if(_info != nullptr || _png != nullptr) {
            png_destroy_write_struct(&_png, &_info);
        }
    }

};

} // namespace fcl::detail


namespace fcl {

class png_image {

public:
    png_image(size_t width, size_t height, std::optional<npp::rgba> bg_col = std::nullopt);

    png_image(png_image&&) = default;
    png_image& operator=(png_image&&) = default;

    png_image(const png_image&) = delete;
    png_image& operator=(const png_image&) = delete;

    size_t width()  const { return _width;  }
    size_t height() const { return _height; }

    npp::rgba& at(size_t x, size_t y) {
        if(x >= _width) {
            throw std::runtime_error(fmt::format("Cannot get x={} for an image where width={}", x, _width));
        }
        if(y >= _height) {
            throw std::runtime_error(fmt::format("Cannot get y={} for an image where height={}", y, _height));
        }
        return _pixels[_width * y + x];
    }

    const npp::rgba& at(size_t x, size_t y) const {
        if(x >= _width) {
            throw std::runtime_error(fmt::format("Cannot get x={} for an image where width={}", x, _width));
        }
        if(y >= _height) {
            throw std::runtime_error(fmt::format("Cannot get y={} for an image where height={}", y, _height));
        }
        return _pixels[_width * y + x];
    }

    std::vector<uint8_t> dump();

private:
    size_t _width;
    size_t _height;

    fcl::detail::png_data_holder _holder;

    std::vector<npp::rgba> _pixels;
};

} // namespace fcl
