#include <vector>
#include <iostream>
#include "zh/fseq.hpp"
#include "zh/proxy_iterator.hpp"
#include "zh/container_view.hpp"
#include "zh/as_functor.hpp"

using container = std::vector<int*>;
using iter = container::iterator;

int& deref(int* ptr) {
	return *ptr;
}

int main() {
	std::cout << std::boolalpha;
	std::cout << zh::is_function_like_v<void()> << std::endl;
	std::cout << zh::is_function_like_v<void(&)()> << std::endl;
	std::cout << zh::is_function_like_v<void(*)()> << std::endl;
	std::cout << zh::is_function_like_v<void(*&)()> << std::endl;
	std::cout << zh::is_function_like_v<void(****&)()> << std::endl;
	std::cout << zh::is_function_like_v<void(*****)()> << std::endl;

	container cc;

	zh::proxy_iterator<iter, zh::as_functor<deref>> p(cc.begin());

	std::cin.get();
}