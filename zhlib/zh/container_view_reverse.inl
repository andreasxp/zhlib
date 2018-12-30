#pragma once
#include "container_view_reverse.hpp"

#define TEMPLATE_CONTAINER_VIEW \
template < \
	class Container, \
	class Iterator, \
	class ConstIterator, \
	class ReverseIterator, \
	class ConstReverseIterator>
#define CONTAINER_VIEW \
container_view< \
	Container, \
	Iterator, \
	ConstIterator, \
	ReverseIterator, \
	ConstReverseIterator, \
	true>

namespace zh {

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::reverse_iterator 
CONTAINER_VIEW::rbegin() noexcept {
	return reverse_iterator(base::end());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::const_reverse_iterator
CONTAINER_VIEW::rbegin() const noexcept {
	return const_reverse_iterator(base::cend());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::const_reverse_iterator
CONTAINER_VIEW::crbegin() const noexcept {
	return const_reverse_iterator(base::cend());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::reverse_iterator
CONTAINER_VIEW::rend() noexcept {
	return reverse_iterator(base::begin());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::const_reverse_iterator
CONTAINER_VIEW::rend() const noexcept {
	return const_reverse_iterator(base::cbegin());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::const_reverse_iterator
CONTAINER_VIEW::crend() const noexcept {
	return const_reverse_iterator(base::cbegin());
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::base::reference
CONTAINER_VIEW::back() {
	return *rbegin();
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::base::const_reference
CONTAINER_VIEW::back() const {
	return *crbegin();
}

} // namespace zh

#undef TEMPLATE_CONTAINER_VIEW
#undef CONTAINER_VIEW