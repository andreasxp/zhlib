#pragma once
#include "container_view.hpp"
#include "container_view_no_reverse.hpp"

namespace zh {

// Specialized container_view with reverse_iterator
// Derive from container_view without reverse_iterator
template <
	class Container,
	class Iterator,
	class ConstIterator,
	class ReverseIterator,
	class ConstReverseIterator>
class container_view <
	Container,
	Iterator,
	ConstIterator,
	ReverseIterator,
	ConstReverseIterator,
	true> : public container_view<
		Container,
		Iterator,
		ConstIterator,
		ReverseIterator,
		ConstReverseIterator,
		false> {
private:
	using base = container_view<
		Container,
		Iterator,
		ConstIterator,
		ReverseIterator,
		ConstReverseIterator,
		false>;

public:
	// ReverseIterator and ConstReverseIterator are void by default.
	// If no iterator was specified, they are defined as
	// std::reverse_iterator<Iterator> and
	// std::reverse_iterator<ConstIterator>
	using reverse_iterator       = std::conditional_t<
		std::is_same_v<ReverseIterator, void>,
		std::reverse_iterator<Iterator>,
		ReverseIterator
	>;

	using const_reverse_iterator = std::conditional_t<
		std::is_same_v<ConstReverseIterator, void>,
		std::reverse_iterator<ConstIterator>,
		ConstReverseIterator
	>;

	// Member functions =======================================================
	using base::base;

	// Iterators --------------------------------------------------------------
	// begin, cbegin, end, cend are derived

	constexpr reverse_iterator rbegin() noexcept;
	constexpr const_reverse_iterator rbegin() const noexcept;
	constexpr const_reverse_iterator crbegin() const noexcept;

	constexpr reverse_iterator rend() noexcept;
	constexpr const_reverse_iterator rend() const noexcept;
	constexpr const_reverse_iterator crend() const noexcept;

	// Observers --------------------------------------------------------------
	// size, empty are derived

	// Element access ---------------------------------------------------------
	// front is derived

	// override back using reverse_iterator
	constexpr typename base::reference back();
	constexpr typename base::const_reference back() const;
};

} // namespace zh

#include "container_view_reverse.inl"