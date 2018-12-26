#pragma once
#include <type_traits>
#include <cstdint>
#include <iostream>
#include <iterator>

namespace zh {

template <class Ptr>
class deriveable_ptr {
	static_assert(std::is_pointer_v<Ptr>,
		"deriveable_ptr: template argument must be a pointer");
private:
	Ptr ptr;

public:
	// Constructors -----------------------------------------------------------
	deriveable_ptr() noexcept = default;

	template <class P, class =
		std::enable_if_t<std::is_constructible_v<Ptr, P>>>
		deriveable_ptr(P&& p) noexcept :
		ptr(p) {
	}

	deriveable_ptr(const deriveable_ptr&) noexcept = default;
	deriveable_ptr(deriveable_ptr&&) noexcept = default;

	deriveable_ptr& operator=(const deriveable_ptr&) noexcept = default;
	deriveable_ptr& operator=(deriveable_ptr&&) noexcept = default;

	template <class P, class =
		std::enable_if_t<std::is_convertible_v<P, Ptr>>>
		deriveable_ptr& operator=(P&& p) {
		ptr = p;
	}

	template <class P, class =
		std::enable_if_t<std::is_convertible_v<Ptr, P>>>
		operator P() const noexcept {
		return ptr;
	}

	// Member functions -------------------------------------------------------
	std::remove_pointer_t<Ptr>& operator*() const noexcept {
		return *ptr;
	}

	Ptr& operator->() const noexcept {
		return ptr;
	}

	deriveable_ptr& operator++() noexcept {
		++ptr;
		return *this;
	}

	deriveable_ptr operator++(int) noexcept {
		deriveable_ptr tmp(*this);
		operator++();
		return tmp;
	}

	deriveable_ptr& operator--() noexcept {
		--ptr;
		return *this;
	}

	deriveable_ptr operator--(int) noexcept {
		deriveable_ptr tmp(*this);
		operator--();
		return tmp;
	}

	deriveable_ptr& operator+=(std::ptrdiff_t offset) noexcept {
		ptr += offset;
		return *this;
	}

	deriveable_ptr& operator-=(std::ptrdiff_t offset) noexcept {
		ptr -= offset;
		return *this;
	}

	std::remove_pointer_t<Ptr>& operator[](std::ptrdiff_t idx) const noexcept {
		return ptr[idx];
	}

	template <class Ptr_>
	friend inline std::ptrdiff_t operator-(deriveable_ptr<Ptr_> lhs, deriveable_ptr<Ptr_> rhs);

	template <class Ptr_>
	friend inline bool operator==(deriveable_ptr<Ptr_> lhs, deriveable_ptr<Ptr_> rhs);
	template <class Ptr_>
	friend inline bool operator< (deriveable_ptr<Ptr_> lhs, deriveable_ptr<Ptr_> rhs);

	template <class Ptr_>
	friend std::ostream& operator<<(std::ostream& os, deriveable_ptr<Ptr_> obj);
	template <class Ptr_>
	friend std::istream& operator>>(std::istream& is, deriveable_ptr<Ptr_> obj);
};

template <class Ptr, class = std::enable_if_t<std::is_pointer_v<Ptr>>>
deriveable_ptr(Ptr)->deriveable_ptr<Ptr>;

template <class Iterator>
using make_deriveable = std::conditional_t<
	std::is_pointer_v<Iterator>,
	deriveable_ptr<Iterator>,
	Iterator
>;

template <class Ptr>
std::ostream& operator<<(std::ostream& os, deriveable_ptr<Ptr> obj) {
	return os << obj.ptr;
}

template <class Ptr>
std::istream& operator>>(std::istream& is, deriveable_ptr<Ptr> obj) {
	return is << obj.ptr;
}

template <class Ptr> inline bool operator==(deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return lhs.ptr == rhs.ptr; }
template <class Ptr> inline bool operator!=(deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return !operator==(lhs, rhs); }
template <class Ptr> inline bool operator< (deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return lhs.ptr < rhs.ptr; }
template <class Ptr> inline bool operator> (deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return  operator< (rhs, lhs); }
template <class Ptr> inline bool operator<=(deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return !operator> (lhs, rhs); }
template <class Ptr> inline bool operator>=(deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) { return !operator< (lhs, rhs); }

template <class Ptr>
inline deriveable_ptr<Ptr> operator+(deriveable_ptr<Ptr> lhs, std::ptrdiff_t offset) {
	lhs += offset;
	return lhs;
}

template <class Ptr>
inline deriveable_ptr<Ptr> operator+(std::ptrdiff_t offset, deriveable_ptr<Ptr> lhs) {
	lhs += offset;
	return lhs;
}

template <class Ptr>
inline deriveable_ptr<Ptr> operator-(deriveable_ptr<Ptr> lhs, std::ptrdiff_t offset) {
	lhs -= offset;
	return lhs;
}

template <class Ptr>
inline std::ptrdiff_t operator-(deriveable_ptr<Ptr> lhs, deriveable_ptr<Ptr> rhs) {
	return lhs.ptr - rhs.ptr;
}

} // namespace zh

namespace std {

template <class Ptr>
struct iterator_traits<zh::deriveable_ptr<Ptr>>
	: iterator_traits<Ptr> {
};

}