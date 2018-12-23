#pragma once
#include <type_traits>
#include <utility>
#include "enable_if_defined.hpp"

namespace zh {

template <class T, class U>
struct is_similar
	: std::is_same<
		std::decay_t<T>, 
		std::decay_t<U>> {
};

template <class T, class U>
constexpr bool is_similar_v = is_similar<T, U>::value;

} // namespace zh