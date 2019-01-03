#include <vector>
#include <iostream>
#include "zh/deriveable_ptr.hpp"
#include "zh/proxy_iterator.hpp"
#include "zh/container_view.hpp"

struct deref_add {
	int how_much;

	int& operator()(int* x) const {
		(*x) += how_much;
		return *x;
	}

	deref_add(int k) {
		how_much = k;
	}
};

using container = std::vector<int*>;
using iter  = typename container::iterator;
using citer = typename container::const_iterator;
using piter  = zh::proxy_iterator<iter,  deref_add>;
using pciter = zh::proxy_iterator<citer, deref_add>;

using cview = zh::forward_container_view<
	container,
	piter,
	pciter,
	deref_add
>;

int main() {
	int x = 5;
	int* xp = &x;

	container v_ = {xp, xp, xp, xp, xp};
	cview v (v_, 2);

	std::cout << v.size() << std::endl;
	//std::cout << v[1] << std::endl;

	for (auto& i : v) {
		std::cout << i << std::endl;
	}

	std::cin.get();
}