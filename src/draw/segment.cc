#include "fcircles/draw/segment.hh"

#include <cassert>

#include <fmt/format.h>


namespace {

template <typename F>
concept vector_mapper = std::invocable<F, npp::vec2<npp::N>> && std::same_as<npp::vec2<npp::N>, std::invoke_result_t<F, npp::vec2<npp::N>>>;

template <vector_mapper Mapper>
std::vector<npp::vec2<npp::N>> segment_helper(npp::vec2<npp::N> vec, Mapper m) {
	assert(vec.x >= 0);
	assert(vec.x >= std::abs(vec.y));
	assert(m(npp::vec2<npp::N>::zero()) == npp::vec2<npp::N>::zero());
	std::vector<npp::vec2<npp::N>> res;
	if(vec.x == 0) {
		if(vec.y >= 0) {
			res.reserve(vec.y);
			for(int64_t i = 0; i <= vec.y; i++) {
				res.push_back(m(npp::vec2<npp::N>(0, i)));
			}
		} else {
			res.reserve(-1 * vec.y);
			for(int64_t i = 0; i >= vec.y; i--) {
				res.push_back(m(npp::vec2<npp::N>(0, i)));
			}
		}
		return res;
	}
	const double a = static_cast<double>(vec.y) / static_cast<double>(vec.x);
	assert(-1 <= a && a <= 1);
	res.emplace_back(0, 0);
	int64_t y = 0;
	double offset = 0;
	bool overshoot = false;
	// fmt::print("x={} y={} a={}\n", vec.x, vec.y, a);
	for(int64_t x = 1; x <= vec.x; x++) {
		// fmt::print("({}, {} + {}) => ", res.back().x, res.back().y, offset);
		offset += a;
		if(offset > 0.5) {
			if(!overshoot) {
				y++;
				overshoot = true;
			}
			if(offset >= 1.0) {
				offset -= 1.0;
				overshoot = false;
			}
		} else if(offset < -0.5) {
			if(!overshoot) {
				y--;
				overshoot = true;
			}
			if(offset <= 1.0) {
				offset += 1.0;
				overshoot = false;
			}
		}
		y = static_cast<int64_t>(std::round(static_cast<double>(x) * a));
		res.push_back(m(npp::vec2<npp::N>(x, y)));
		// fmt::print("({}, {} + {})\n", res.back().x, res.back().y, offset);
	}
	return res;
}

} // anonymous namespace


namespace fcl {

std::vector<npp::vec2<npp::N>> compute_segment_points(npp::vec2<npp::N> vec) {
	static constexpr auto invert_x = [](npp::vec2<npp::N> v) { return npp::vec2<npp::N>(-1 * v.x, v.y); };
	static constexpr auto swap_coords = [](npp::vec2<npp::N> v) { return npp::vec2<npp::N>(v.y, v.x); };
	if(std::abs(vec.x) < std::abs(vec.y)) {
		if(vec.y < 0) {
			return ::segment_helper(invert_x(swap_coords(vec)), [](npp::vec2<npp::N> v) { return swap_coords(invert_x(v)); });
		}
		return ::segment_helper(swap_coords(vec), swap_coords);
	}
	if(vec.x < 0) {
		return ::segment_helper(invert_x(vec), invert_x);
	}
	return ::segment_helper(vec, [](npp::vec2<npp::N> v) { return v; });
}

} // namespace fcl
