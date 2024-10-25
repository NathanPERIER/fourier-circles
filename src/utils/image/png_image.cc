
#include "fcircles/utils/image/png_image.hh"

#include <cassert>
#include <stdexcept>


namespace {

void write_png_data_buf(png_struct* png, png_byte* data, png_size_t size) {
    std::vector<uint8_t>& buf = *reinterpret_cast<std::vector<uint8_t>*>(png_get_io_ptr(png));
    buf.insert(buf.end(), data, data + size);
}

void write_png_flush_buf(png_struct* png) {
    (void) png; // nothing to do here
}

} // anonymous namespace



namespace fcl::detail {

void png_data_holder::init() {
    if(_info != nullptr || _png != nullptr) {
        return;
    }

    _png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(_png == nullptr) {
        throw std::runtime_error("Error while allocating PNG structure");
    }

    _info = png_create_info_struct(_png);
    if(_info == nullptr) {
        // TODO check that PNG structure is freed
        throw std::runtime_error("Error while allocating PNG info structure");
    }
}

} // namespace fcl::detail



namespace fcl {

png_image::png_image(size_t width, size_t height, std::optional<rgba> bg_col): _width(width), _height(height) {
    _holder.init();

    png_set_IHDR(
        _holder.png(),
        _holder.info(),
        _width, _height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    const size_t row_bytes = png_get_rowbytes(_holder.png(), _holder.info());
    assert(row_bytes == (_width * sizeof(rgba)));
    if(bg_col.has_value()) {
        _pixels.resize(_width * _height, bg_col.value());
    } else {
        _pixels.resize(_width * _height);
    }
}

std::vector<uint8_t> png_image::dump() {
    std::vector<png_byte*> row_pointers;
    row_pointers.reserve(_height);
    for(size_t y = 0; y < _height; y++) {
        row_pointers.push_back(reinterpret_cast<png_byte*>(_pixels.data() + y * _width));
    }

    std::vector<uint8_t> res;
    png_set_write_fn(_holder.png(), &res, ::write_png_data_buf, ::write_png_flush_buf);
    
    png_write_info(_holder.png(), _holder.info());
    png_write_image(_holder.png(), row_pointers.data()); // Warning: systematic copy here
    png_write_end(_holder.png(), nullptr);

    return res;
}

} // namespace fcl
