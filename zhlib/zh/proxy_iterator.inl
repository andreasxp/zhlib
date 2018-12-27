#pragma once
#include "proxy_iterator.hpp"

namespace zh {

template <class Iterator, class Functor>
typename proxy_iterator<Iterator, Functor>::base&
proxy_iterator<Iterator, Functor>::iterator() noexcept {
	return static_cast<base&>(*this);
}

template <class Iterator, class Functor>
const typename proxy_iterator<Iterator, Functor>::base&
proxy_iterator<Iterator, Functor>::iterator() const noexcept {
	return static_cast<const base&>(*this);
}

template <class Iterator, class Functor>
typename proxy_iterator<Iterator, Functor>::functor_type&
proxy_iterator<Iterator, Functor>::functor() noexcept {
	return static_cast<functor_type&>(*this);
}

template <class Iterator, class Functor>
const typename proxy_iterator<Iterator, Functor>::functor_type&
proxy_iterator<Iterator, Functor>::functor() const noexcept {
	return static_cast<const functor_type&>(*this);
}

template <class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>::
proxy_iterator(const iterator_type& other, const functor_type& functor)
noexcept(
	std::is_nothrow_copy_constructible_v<iterator_type> &&
	std::is_nothrow_copy_constructible_v<functor_type>) :
	iterator_type(other),
	functor_type(functor) {
}

template <class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>::
proxy_iterator(const functor_type& functor)
noexcept(proxy_iterator(iterator_type(), functor)) :
	proxy_iterator(iterator_type(), functor) {
}

template <class Iterator, class Functor>
template <class Iter, class>
constexpr proxy_iterator<Iterator, Functor>::
proxy_iterator(const proxy_iterator<Iter, functor_type>& other)
noexcept(
	std::is_nothrow_constructible_v<iterator_type, const Iter&> &&
	std::is_nothrow_default_constructible_v<functor_type>) :
	iterator_type(other.iterator()) {
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>::operator iterator_type() const noexcept {
	return iterator();
}

template<class Iterator, class Functor>
constexpr typename proxy_iterator<Iterator, Functor>::iterator_type
proxy_iterator<Iterator, Functor>::get_iterator() const noexcept {
	return iterator();
}

template<class Iterator, class Functor>
constexpr typename proxy_iterator<Iterator, Functor>::functor_type
proxy_iterator<Iterator, Functor>::get_functor() const noexcept {
	return functor();
}

template <class Iterator, class Functor>
constexpr decltype(auto) proxy_iterator<Iterator, Functor>::operator->() const
noexcept(std::addressof(functor()(*iterator()))) {
	return std::addressof(functor()(*iterator()));
}

template <class Iterator, class Functor>
constexpr decltype(auto) proxy_iterator<Iterator, Functor>::operator*() const
noexcept(functor()(*iterator())) {
	return functor()(*iterator());
}

template<class Iterator, class Functor>
constexpr decltype(auto)
proxy_iterator<Iterator, Functor>::operator[](difference_type idx) const noexcept {
	return iterator()[idx];
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>&
proxy_iterator<Iterator, Functor>::operator++() noexcept {
	++iterator();
	return *this;
}

template<class Iterator, class Functor>
inline constexpr proxy_iterator<Iterator, Functor>
proxy_iterator<Iterator, Functor>::operator++(int) noexcept {
	proxy_iterator tmp(*this);
	operator++();
	return tmp;
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>&
proxy_iterator<Iterator, Functor>::operator--() noexcept {
	--iterator();
	return *this;
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>
proxy_iterator<Iterator, Functor>::operator--(int) noexcept {
	proxy_iterator tmp(*this);
	operator--();
	return tmp;
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>&
proxy_iterator<Iterator, Functor>::operator+=(difference_type offset) noexcept {
	iterator() += offset;
	return *this;
}

template<class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>&
proxy_iterator<Iterator, Functor>::operator-=(difference_type offset) noexcept {
	iterator() -= offset;
	return *this;
}

template <class Iterator, class Functor>
constexpr bool operator==(const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return lhs.iterator() == rhs.iterator();
}

template <class Iterator, class Functor>
constexpr bool operator!=(const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return !(lhs == rhs);
}

template <class Iterator, class Functor>
constexpr bool operator< (const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return lhs.iterator() < rhs.iterator();
}

template <class Iterator, class Functor>
constexpr bool operator> (const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return rhs < lhs;
}

template <class Iterator, class Functor>
constexpr bool operator<=(const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return !(lhs > rhs);
}

template <class Iterator, class Functor>
constexpr bool operator>=(const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return !(lhs < rhs);
}

template <class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>
operator+(const proxy_iterator<Iterator, Functor>& lhs, typename proxy_iterator<Iterator, Functor>::difference_type offset) {
	return proxy_iterator<Iterator, Functor>(lhs.iterator() + offset, lhs.functor());
}

template <class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>
operator+(typename proxy_iterator<Iterator, Functor>::difference_type offset, const proxy_iterator<Iterator, Functor>& lhs) {
	return lhs + offset;
}

template <class Iterator, class Functor>
constexpr proxy_iterator<Iterator, Functor>
operator-(const proxy_iterator<Iterator, Functor>& lhs, typename proxy_iterator<Iterator, Functor>::difference_type offset) {
	return proxy_iterator<Iterator, Functor>(lhs.iterator() - offset, lhs.functor());
}

template <class Iterator, class Functor>
constexpr typename proxy_iterator<Iterator, Functor>::difference_type
operator-(const proxy_iterator<Iterator, Functor>& lhs, const proxy_iterator<Iterator, Functor>& rhs) {
	return lhs.iterator() - rhs.iterator();
}

} // namespace zh