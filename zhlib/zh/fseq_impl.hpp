#pragma once
#include <utility>

namespace zh {
namespace detail {

// fseq_impl is the implementation of functor sequence
// accepts void parameter as a marker of end.

// Disable base class ambiguity warnings
#if defined __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmicrosoft-inaccessible-base"
#pragma clang diagnostic ignored "-Winaccessible-base"
#elif defined __GNUC__
// g++ does not warn
#elif defined _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4584)
#endif

template <class Functor1, class... Functors>
struct fseq_impl : private Functor1, private fseq_impl<Functors...> {
private:
	using base = fseq_impl<Functors...>;

public:
	template <class T>
	decltype(auto) operator()(T&& obj) {
		return static_cast<base&>(*this)(
			static_cast<Functor1&>(*this)(std::forward<T>(obj))
			);
	}

	template <class T>
	decltype(auto) operator()(T&& obj) const {
		return static_cast<const base&>(*this)(
			static_cast<const Functor1&>(*this)(std::forward<T>(obj))
			);
	}

	fseq_impl() = default;

	template <class UFunctor1, class... UFunctors>
	explicit fseq_impl(UFunctor1 functor1, UFunctors... functors) :
		Functor1(functor1),
		base(functors...) {
	}
};

#if defined __clang__
#pragma clang diagnostic pop
#elif defined __GNUC__
// g++ does not warn
#elif defined _MSC_VER
#pragma warning(pop) 
#endif

template <class Functor>
struct fseq_impl<Functor, void> : private Functor {
	template <class T>
	decltype(auto) operator()(T&& obj) {
		return static_cast<Functor&>(*this)(std::forward<T>(obj));
	}

	template <class T>
	decltype(auto) operator()(T&& obj) const {
		return static_cast<const Functor&>(*this)(std::forward<T>(obj));
	}

	fseq_impl() = default;

	template <class UFunctor>
	explicit fseq_impl(UFunctor functor) :
		Functor(functor) {
	}
};

template<class... UFunctors>
fseq_impl(UFunctors...)->fseq_impl<UFunctors...>;

} // namespace detail
} // namespace zh
