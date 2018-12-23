#pragma once
#include <iterator>
#include <type_traits>
#include "type_traits.hpp"
#include "proxy_iterator.hpp"

namespace zh {

struct empty {};

// container_view
// This class provides access to a class using some custom iterators.
// For example, container_view can be used with proxy_iterators to "view"
// a container through a proxy, such as view an array of pointers as an array
// of normal elements, complete with the ability to access and modify elements.
// Note: this container is not user-friendly. Recommended usage is through the
// zh::view function.
template <
	class Container,
	class Iterator, 
	class ConstIterator, 
	class ReverseIterator,
	class ConstReverseIterator,
	class OptionalFunctorType = empty>
class container_view : private OptionalFunctorType {
private:
	Container& c;

	// Shortcuts --------------------------------------------------------------
	constexpr static bool is_reversible = !std::is_same_v<ReverseIterator, void>;
	constexpr static bool has_back = is_reversible ||
		std::is_base_of_v<std::bidirectional_iterator_tag, 
		typename std::iterator_traits<Iterator>::iterator_category>;
	constexpr static bool has_random_access = 
		std::is_base_of_v<std::random_access_iterator_tag,
		typename std::iterator_traits<Iterator>::iterator_category>;
	constexpr static bool has_explicit_functor =
		!std::is_same_v<OptionalFunctorType, empty>;
public:
	// Member types ===========================================================
	using value_type = typename
		std::iterator_traits<Iterator>::value_type;
	using difference_type = typename
		std::iterator_traits<Iterator>::difference_type;
	using reference = typename
		std::iterator_traits<Iterator>::reference;
	using const_reference = typename
		std::iterator_traits<ConstIterator>::reference;
	using pointer = typename
		std::iterator_traits<Iterator>::pointer;
	using const_pointer = typename
		std::iterator_traits<ConstIterator>::pointer;

	using iterator = Iterator;
	using const_iterator = ConstIterator;

	template <class = std::enable_if_t<is_reversible>>
	using reverse_iterator = ReverseIterator;

	template <class = std::enable_if_t<is_reversible>>
	using const_reverse_iterator = ConstReverseIterator;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	template <class = std::enable_if_t<!std::is_same_v<
		OptionalFunctorType, empty>>>
	constexpr container_view(Container& container, OptionalFunctorType f);
	constexpr container_view(Container& container);
	~container_view() = default;

	// Iterators --------------------------------------------------------------
	constexpr Iterator begin() noexcept;
	constexpr ConstIterator begin() const noexcept;
	constexpr ConstIterator cbegin() const noexcept;

	constexpr Iterator end() noexcept;
	constexpr ConstIterator end() const noexcept;
	constexpr ConstIterator cend() const noexcept;

	template <class = std::enable_if_t<is_reversible>>
	constexpr ReverseIterator rbegin() noexcept;
	template <class = std::enable_if_t<is_reversible>>
	constexpr ConstReverseIterator rbegin() const noexcept;
	template <class = std::enable_if_t<is_reversible>>
	constexpr ConstReverseIterator crbegin() const noexcept;

	template <class = std::enable_if_t<is_reversible>>
	constexpr ReverseIterator rend() noexcept;
	template <class = std::enable_if_t<is_reversible>>
	constexpr ConstReverseIterator rend() const noexcept;
	template <class = std::enable_if_t<is_reversible>>
	constexpr ConstReverseIterator crend() const noexcept;

	// Observers --------------------------------------------------------------
	template <class = std::enable_if_t<has_size_v<Container>>>
	constexpr std::size_t size() const noexcept;

	template <class = std::enable_if_t<has_size_v<Container>>>
	constexpr bool empty() const noexcept;

	// Element access ---------------------------------------------------------
	constexpr reference front();

	constexpr const_reference front() const;

	template <class = std::enable_if_t<has_back>>
	constexpr reference back();

	template <class = std::enable_if_t<has_back>>
	constexpr const_reference back() const;

	template <class = std::enable_if_t<has_random_access>>
	constexpr reference operator[](std::size_t index);

	template <class = std::enable_if_t<has_random_access>>
	constexpr const_reference operator[](std::size_t index) const;
};

template <class Container, class FunctorType>
container_view(Container& c, FunctorType) ->
container_view<Container,
	proxy_iterator<decltype(c.begin()), FunctorType>,
	proxy_iterator<decltype(c.cbegin()), FunctorType>, 
	std::conditional_t<is_bidirectional_range_v<Container>, proxy_iterator<decltype(c.rbegin()), FunctorType>, void>,
	std::conditional_t<is_bidirectional_range_v<Container>, proxy_iterator<decltype(c.crbegin()), FunctorType>, void>,
	FunctorType
>;

template <template <class Iterator> class ProxyIterator, class Container>
constexpr auto view(Container& container);

template <class Container, class Functor>
constexpr auto view(Container& container, Functor&& f);

} // namespace zh

#include "container_view.inl"