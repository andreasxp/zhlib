#include <vector>
#include <iostream>
#include "zh/deriveable_ptr.hpp"
#include "zh/proxy_iterator.hpp"

using container = std::vector<int*>;
using iter = typename container::iterator;
using proxy = zh::proxy_iterator<iter, zh::proxy::dereference>;

int main() {
	

	std::cin.get();
}