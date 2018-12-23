#pragma once
#include "container_view.hpp"

#define TEMPLATE_CONTAINER_VIEW \
template < \
class Container, \
	class Iterator, \
	class ConstIterator, \
	class ReverseIterator, \
	class ConstReverseIterator, \
	class OptionalFunctorType>
#define CONTAINER_VIEW \
container_view<Container, \
	Iterator, \
	ConstIterator, \
	ReverseIterator, \
	ConstReverseIterator, \
	OptionalFunctorType>

namespace zh {

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr CONTAINER_VIEW::container_view(Container& container, OptionalFunctorType f) :
	OptionalFunctorType(f),
	c(container) {
}

TEMPLATE_CONTAINER_VIEW
constexpr CONTAINER_VIEW::container_view(Container& container) :
	c(container) {
}

TEMPLATE_CONTAINER_VIEW
constexpr Iterator CONTAINER_VIEW::begin() noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::begin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::begin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::begin() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::cbegin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::cbegin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::cbegin() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::cbegin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::cbegin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
constexpr Iterator CONTAINER_VIEW::end() noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::end(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::end(c));
	}
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::end() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::cend(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::cend(c));
	}
}

TEMPLATE_CONTAINER_VIEW
constexpr ConstIterator CONTAINER_VIEW::cend() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::cend(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::cend(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ReverseIterator CONTAINER_VIEW::rbegin() noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::rbegin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::rbegin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ConstReverseIterator CONTAINER_VIEW::rbegin() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::crbegin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::crbegin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ConstReverseIterator CONTAINER_VIEW::crbegin() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::crbegin(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::crbegin(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ReverseIterator CONTAINER_VIEW::rend() noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::rend(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::rend(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ConstReverseIterator CONTAINER_VIEW::rend() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::crend(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::crend(c));
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr ConstReverseIterator CONTAINER_VIEW::crend() const noexcept {
	if constexpr (has_explicit_functor) {
		return Iterator(std::crend(c), static_cast<OptionalFunctorType&>(*this));
	}
	else {
		return Iterator(std::crend(c));
	}
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
	if constexpr (is_reversible) {
		return *rbegin();
	}
	else {
		return *std::prev(end());
	}
}

TEMPLATE_CONTAINER_VIEW
template <class>
constexpr typename CONTAINER_VIEW::const_reference 
CONTAINER_VIEW::back() const {
	if constexpr (is_reversible) {
		return *crbegin();
	}
	else {
		return *std::prev(cend());
	}
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

template <template <class Iterator> class ProxyIterator, class Container>
constexpr auto view(Container& container) {
	// If has reverse_iterators, include them
	if constexpr (is_bidirectional_range_v<Container>) {
		return container_view<
			Container,
			ProxyIterator<decltype(container.begin())>,
			ProxyIterator<decltype(container.cbegin())>,
			ProxyIterator<decltype(container.rbegin())>,
			ProxyIterator<decltype(container.crbegin())>>
			(container);
	}
	// Otherwise container_view will have no rbegin and rend
	else {
		return container_view<
			Container,
			ProxyIterator<decltype(container.begin())>,
			ProxyIterator<decltype(container.cbegin())>,
			void,
			void>
			(container);
	}
}

template <class Container, class Functor>
constexpr auto view(Container& container, Functor&& f) {
	// If has reverse_iterators, include them
	if constexpr (is_bidirectional_range_v<Container>) {
		return container_view(container, f);
	}
	// Otherwise container_view will have no rbegin and rend
	else {
		return container_view<
			Container,
			proxy_iterator<decltype(container.begin()), Functor>,
			proxy_iterator<decltype(container.cbegin()), Functor>,
			void,
			void,
			Functor>
			(container, f);
	}
}

} // namespace zh