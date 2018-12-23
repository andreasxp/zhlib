#include <vector>
#include <iostream>
#include "zh/fseq.hpp"
#include "zh/proxy_iterator.hpp"
#include "zh/container_view.hpp"

using container = std::vector<int*>;
using iter = container::iterator;
using proxy = zh::proxy_iterator<iter,
	zh::proxy::dereference>;

template <class T>
using proxy_t = zh::proxy_iterator<T,
	zh::proxy::dereference>;

int main() {
	container data;
	zh::container_view v(data, [](auto&& v) {return *v; });
	//auto v = zh::view(data, [](auto&& v) {return *v; });


	// Fill
	int x = 5;
	int* xp = &x;
	for (int i = 0; i < 15; ++i) {
		data.push_back(xp);
	}

	// Print
	for (auto i : v) {
		std::cout << i;
	}
	std::cout << std::endl;

	// Print
	for (proxy it(data.begin()); it != proxy(data.end()); ++it) {
		std::cout << *it;
	}

	std::cin.get();
}