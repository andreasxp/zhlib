#pragma once
#include "container_view_impl.hpp"
#include "container_view_impl_no_reverse.hpp"

namespace zh {
namespace detail {

// Specialized container_view_impl with reverse_iterator
// Derive from container_view_impl without reverse_iterator
template <
	class Container,
	class Iterator,
	class ConstIterator,
	class ReverseIterator,
	class ConstReverseIterator,
	class... Args>
class container_view_impl <
	Container,
	Iterator,
	ConstIterator,
	ReverseIterator,
	ConstReverseIterator,
	true,
	Args...> : public container_view_impl<
		Container,
		Iterator,
		ConstIterator,
		ReverseIterator,
		ConstReverseIterator,
		false,
		Args...> {
private:
	using base = container_view_impl<
		Container,
		Iterator,
		ConstIterator,
		ReverseIterator,
		ConstReverseIterator,
		false,
		Args...>;

public:
	using reverse_iterator       = ReverseIterator;
	using const_reverse_iterator = ConstReverseIterator;

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

} // namespace detail
} // namespace zh

#include "container_view_impl_reverse.inl"