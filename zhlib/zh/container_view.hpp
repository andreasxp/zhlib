#pragma once
#include <type_traits>
#include <iterator>

namespace zh {

// container_view
// This class provides access to a class using some custom iterators.
// For example, container_view can be used with proxy_iterators to "view"
// a container through a proxy, such as view an array of pointers as an array
// of normal elements, complete with the ability to access and modify elements.

template <
	class Container,
	class Iterator,
	class ConstIterator,
	class ReverseIterator = void, // If needed, reverse iterators will be defined as std::reverse_iterator
	class ConstReverseIterator = void,
	bool use_reverse = std::is_base_of_v<
		std::bidirectional_iterator_tag,
		typename std::iterator_traits<Iterator>::iterator_category>>
class container_view;

template <
	class Container,
	class ConstIterator,
	class ConstReverseIterator = void>
	using const_container_view = container_view<
	Container const,
	ConstIterator,
	ConstIterator,
	ConstReverseIterator,
	ConstReverseIterator
>;

// Explicitly forbid reverse_iterators
template <
	class Container,
	class Iterator,
	class ConstIterator>
	using forward_container_view = container_view<
	Container,
	Iterator,
	ConstIterator,
	void,
	void,
	false
>;

template <
	class Container,
	class ConstIterator>
	using const_forward_container_view = container_view<
	Container const,
	ConstIterator,
	ConstIterator,
	void,
	void,
	false
>;

} // namespace zh

#include "container_view_reverse.hpp"
#include "container_view_no_reverse.hpp"