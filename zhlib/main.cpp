#include <vector>
#include <iostream>
#include "zh/deriveable_ptr.hpp"
#include "zh/proxy_iterator.hpp"
#include "zh/container_view.hpp"

using container = std::vector<int*>;
using iter =  typename container::iterator;
using citer = typename container::const_iterator;
using proxy = zh::proxy_iterator<iter, zh::proxy::dereference>;

using cview = zh::container_view<
	container,
	iter,
	citer
>;

int main() {
	int x = 5;
	int* xp = &x;

	container v_ = {xp, xp, xp, xp, xp};
	cview v = v_;

	std::cout << v.size();
	std::cout << v[1] << std::endl;

	for (auto it = v.rbegin(); it != v.rend(); ++it) {
		std::cout << *it << std::endl;
	}

	std::cin.get();
}