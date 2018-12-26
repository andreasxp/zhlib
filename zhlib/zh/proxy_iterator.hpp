#pragma once
#include <iterator>
#include <memory>
#include <type_traits>
#include "deriveable_ptr.hpp"
#include "type_traits/is_function_like.hpp"
#include "as_functor.hpp"

namespace zh {

template <class BaseIterator, class FunctorType>
class proxy_iterator : 
	public make_deriveable<BaseIterator>,
	private FunctorType {
public:
	// Member types ------------------------------------------------------------
	using iterator_type = BaseIterator;
	using functor_type = FunctorType;

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

	// Member functions -------------------------------------------------------
	explicit constexpr proxy_iterator(
		const iterator_type& other = iterator_type(), 
		const functor_type& functor = functor_type())
		noexcept(
			std::is_nothrow_copy_constructible_v<iterator_type> &&
			std::is_nothrow_copy_constructible_v<functor_type>) :
		iterator_type(other),
		functor_type (functor) {
	}

	explicit constexpr proxy_iterator(const functor_type& functor)
		noexcept(proxy_iterator(iterator_type(), functor)) :
		proxy_iterator(iterator_type(), functor) {
	}

	// Convert from related proxy iterators
	// Example: proxy_iterator<iterator, ...> to 
	//          proxy_iterator<const_iterator, ...>
	template<class Iter, class = 
		std::enable_if_t<std::is_constructible_v<iterator_type, const Iter&>>>
	constexpr proxy_iterator(const proxy_iterator<Iter, functor_type>& other)
		noexcept(
			std::is_nothrow_constructible_v<iterator_type, const Iter&> &&
			std::is_nothrow_default_constructible_v<functor_type>) :
		iterator_type(static_cast<const Iter&>(other)) {
	}

	constexpr decltype(auto) operator->() const
		noexcept(std::addressof(
			functor_type::operator()(*static_cast<const iterator_type&>(*this)))) {
		return std::addressof(
			functor_type::operator()(*static_cast<const iterator_type&>(*this)));
	}

	constexpr decltype(auto) operator*() const
		noexcept(
			functor_type::operator()(*static_cast<const iterator_type&>(*this))) {
		return 
			functor_type::operator()(*static_cast<const iterator_type&>(*this));
	}
};

} // namespace zh

// Expose default functors
#include "iterator_functors.hpp"