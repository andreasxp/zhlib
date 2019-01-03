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

protected:
	using container_type = typename base::container_type;
	using iterator_args  = typename base::iterator_args;

public:
	// Member types ===========================================================
	using value_type      = typename base::value_type;
	using difference_type = typename base::difference_type;
	using reference       = typename base::reference;
	using const_reference = typename base::const_reference;
	using pointer         = typename base::pointer;
	using const_pointer   = typename base::const_pointer;

	using iterator        = typename base::iterator;
	using const_iterator  = typename base::const_iterator;
	using reverse_iterator       = ReverseIterator;
	using const_reverse_iterator = ConstReverseIterator;

	// Although redefining all member types is of questionable use, it makes
	// code easier to read, and in case of reference and const_reference is
	// actually required, because overriden back() methods below fail to
	// compile with return type base::reference due to a bug in MSVC.

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
	constexpr reference back();
	constexpr const_reference back() const;
};

} // namespace detail
} // namespace zh

#include "container_view_impl_reverse.inl"