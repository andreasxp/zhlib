#pragma once
#include <iterator>
#include <memory>
#include <type_traits>
#include "deriveable_ptr.hpp"
#include "type_traits/is_function_like.hpp"
#include "as_functor.hpp"

namespace zh {

template <class Iterator, class Functor>
class proxy_iterator : 
	private make_deriveable<Iterator>,
	private Functor {
public:
	// Member types -----------------------------------------------------------

	// Iterator that was used to instantiate proxy_iterator
	using iterator_type = Iterator;
	using functor_type = Functor;

private:
	// Private types and functions --------------------------------------------

	// Actual base iterator type from which the class is derived
	using base = make_deriveable<Iterator>;

	base& iterator() noexcept;
	const base& iterator() const noexcept;

	functor_type& functor() noexcept;
	const functor_type& functor() const noexcept;

public:
	// Member types (cont.) ---------------------------------------------------
	using value_type
		= typename std::remove_reference_t<decltype(
			std::declval<functor_type>()(*std::declval<iterator_type>()))>;
	using difference_type
		= typename std::iterator_traits<iterator_type>::difference_type;
	using pointer
		= value_type * ;
	using reference
		= value_type & ;
	using iterator_category
		= typename std::iterator_traits<iterator_type>::iterator_category;

	// Constructors -----------------------------------------------------------
	explicit constexpr proxy_iterator(
		const iterator_type& other = iterator_type(),
		const functor_type& functor = functor_type())
		noexcept(
			std::is_nothrow_copy_constructible_v<iterator_type> &&
			std::is_nothrow_copy_constructible_v<functor_type>);

	explicit constexpr proxy_iterator(const functor_type& functor)
		noexcept(proxy_iterator(iterator_type(), functor));

	// Convert from related proxy iterators
	// Example: proxy_iterator<iterator, ...> to 
	//          proxy_iterator<const_iterator, ...>
	template<class Iter, class = 
		std::enable_if_t<std::is_constructible_v<iterator_type, const Iter&>>>
	constexpr proxy_iterator(const proxy_iterator<Iter, functor_type>& other)
		noexcept(
			std::is_nothrow_constructible_v<iterator_type, const Iter&> &&
			std::is_nothrow_default_constructible_v<functor_type>);

	// Converters -------------------------------------------------------------
	// Unlike private methods that return references, these methods return
	// copies. Also, while private method iterator() returns base, get_iterator
	// returns iterator_type, which may or may not be different.

	explicit constexpr operator iterator_type() const noexcept;

	constexpr iterator_type get_iterator() const noexcept;
	constexpr functor_type get_functor() const noexcept;

	// Member functions -------------------------------------------------------

	constexpr decltype(auto) operator->() const
		noexcept(std::addressof(functor()(*iterator())));

	constexpr decltype(auto) operator*() const
		noexcept(functor()(*iterator()));

	// Some of the following methods may or may not be present in base iterator.
	// Since this is a templated class, these methods will fail to compile only
	// if used somewhere in the program. No SFINAE needed.

	constexpr decltype(auto) operator[](difference_type idx) const noexcept;

	constexpr proxy_iterator& operator++() noexcept;
	constexpr proxy_iterator operator++(int) noexcept;

	constexpr proxy_iterator& operator--() noexcept;
	constexpr proxy_iterator operator--(int) noexcept;

	constexpr proxy_iterator& operator+=(difference_type offset) noexcept;
	constexpr proxy_iterator& operator-=(difference_type offset) noexcept;

	// Friends ----------------------------------------------------------------
	template <class Iterator_, class Functor_>
	friend constexpr bool operator==(
		const proxy_iterator<Iterator_, Functor_>& lhs, const proxy_iterator<Iterator_, Functor_>& rhs);

	template <class Iterator_, class Functor_>
	friend constexpr bool operator!=(
		const proxy_iterator<Iterator_, Functor_>& lhs, const proxy_iterator<Iterator_, Functor_>& rhs);

	template <class Iterator_, class Functor_>
	friend constexpr bool operator< (
		const proxy_iterator<Iterator_, Functor_>& lhs, const proxy_iterator<Iterator_, Functor_>& rhs);

	template <class Iterator_, class Functor_>
	friend constexpr proxy_iterator<Iterator_, Functor_>
		operator+(
			const proxy_iterator<Iterator_, Functor_>& lhs, 
			typename proxy_iterator<Iterator_, Functor_>::difference_type offset);
	
	template <class Iterator_, class Functor_>
	friend constexpr proxy_iterator<Iterator_, Functor_>
		operator-(
			const proxy_iterator<Iterator_, Functor_>& lhs, 
			typename proxy_iterator<Iterator_, Functor_>::difference_type offset);

	template <class Iterator_, class Functor_>
	friend constexpr typename proxy_iterator<Iterator_, Functor_>::difference_type
		operator-(
			const proxy_iterator<Iterator_, Functor_>& lhs, 
			const proxy_iterator<Iterator_, Functor_>& rhs);
};

template <class Iterator, class Functor> 
constexpr bool operator==(
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr bool operator!=(
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr bool operator< (
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr bool operator> (
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr bool operator<=(
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr bool operator>=(
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);

template <class Iterator, class Functor> 
constexpr proxy_iterator<Iterator, Functor> 
operator+(
	const proxy_iterator<Iterator, Functor>& lhs, 
	typename proxy_iterator<Iterator, Functor>::difference_type offset);

template <class Iterator, class Functor> 
constexpr proxy_iterator<Iterator, Functor> 
operator+(
	typename proxy_iterator<Iterator, Functor>::difference_type offset, 
	const proxy_iterator<Iterator, Functor>& lhs);

template <class Iterator, class Functor> 
constexpr proxy_iterator<Iterator, Functor> 
operator-(
	const proxy_iterator<Iterator, Functor>& lhs, 
	typename proxy_iterator<Iterator, Functor>::difference_type offset);

template <class Iterator, class Functor> 
constexpr typename proxy_iterator<Iterator, Functor>::difference_type 
operator-(
	const proxy_iterator<Iterator, Functor>& lhs, 
	const proxy_iterator<Iterator, Functor>& rhs);


} // namespace zh

// Expose default functors
#include "iterator_functors.hpp"

#include "proxy_iterator.inl"