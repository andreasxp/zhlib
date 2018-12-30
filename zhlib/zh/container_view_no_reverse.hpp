#pragma once
#include "container_view.hpp"
#include "type_traits/has_size.hpp"

namespace zh {

// Specialized container_view with no reverse_iterator
template <
	class Container,
	class Iterator,
	class ConstIterator,
	class ReverseIterator,
	class ConstReverseIterator>
class container_view<
	Container,
	Iterator,
	ConstIterator,
	ReverseIterator,
	ConstReverseIterator,
	false> {
protected:
	Container& c;
	
	// Shortcuts --------------------------------------------------------------
	constexpr static bool has_back = std::is_base_of_v<
		std::bidirectional_iterator_tag,
		typename std::iterator_traits<Iterator>::iterator_category>;

	constexpr static bool has_random_access =
		std::is_base_of_v<std::random_access_iterator_tag,
		typename std::iterator_traits<Iterator>::iterator_category>;

public:
	// Member types ===========================================================
	using value_type      = typename std::iterator_traits<Iterator>     ::value_type;
	using difference_type = typename std::iterator_traits<Iterator>     ::difference_type;
	using reference       = typename std::iterator_traits<Iterator>     ::reference;
	using const_reference = typename std::iterator_traits<ConstIterator>::reference;
	using pointer         = typename std::iterator_traits<Iterator>     ::pointer;
	using const_pointer   = typename std::iterator_traits<ConstIterator>::pointer;

	using iterator = Iterator;
	using const_iterator = ConstIterator;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	constexpr container_view(Container& container);
	~container_view() = default;

	// Iterators --------------------------------------------------------------
	constexpr Iterator begin() noexcept;
	constexpr ConstIterator begin() const noexcept;
	constexpr ConstIterator cbegin() const noexcept;

	constexpr Iterator end() noexcept;
	constexpr ConstIterator end() const noexcept;
	constexpr ConstIterator cend() const noexcept;

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

} // namespace zh

#include "container_view_no_reverse.inl"