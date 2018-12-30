#pragma once
#include "container_view_no_reverse.hpp"

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
	false>

namespace zh {

TEMPLATE_CONTAINER_VIEW
constexpr CONTAINER_VIEW::container_view(Container& container) :
	c(container) {
}

TEMPLATE_CONTAINER_VIEW
constexpr Iterator CONTAINER_VIEW::begin() noexcept {
	return Iterator(std::begin(c));
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::begin() const noexcept {
	return ConstIterator(std::cbegin(c));
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::cbegin() const noexcept {
	return ConstIterator(std::cbegin(c));
}

TEMPLATE_CONTAINER_VIEW
constexpr Iterator CONTAINER_VIEW::end() noexcept {
	return Iterator(std::end(c));
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::end() const noexcept {
	return ConstIterator(std::cend(c));
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::cend() const noexcept {
	return ConstIterator(std::cend(c));
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr std::size_t CONTAINER_VIEW::size() const noexcept {
	return std::size(c);
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr bool CONTAINER_VIEW::empty() const noexcept {
	return std::empty(c);
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::reference
CONTAINER_VIEW::front() {
	return *begin();
}

TEMPLATE_CONTAINER_VIEW
constexpr typename CONTAINER_VIEW::const_reference
CONTAINER_VIEW::front() const {
	return *cbegin();
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr typename CONTAINER_VIEW::reference
CONTAINER_VIEW::back() {
	return *std::prev(end());
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr typename CONTAINER_VIEW::const_reference
CONTAINER_VIEW::back() const {
	return *std::prev(cend());
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr typename CONTAINER_VIEW::reference
CONTAINER_VIEW::operator[](std::size_t index) {
	return *(begin() + index);
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr typename CONTAINER_VIEW::const_reference
CONTAINER_VIEW::operator[](std::size_t index) const {
	return *(cbegin() + index);
}

} // namespace zh

#undef TEMPLATE_CONTAINER_VIEW
#undef CONTAINER_VIEW