#include <vector>
#include <iostream>
#include "zh/deriveable_ptr.hpp"

int main() {
	int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 9};
	int* const ptr = x;
	zh::deriveable_ptr p(ptr);

	std::cout << p << std::endl;
	p++;
	++p;
	p--;
	--p;
	std::cout << *p << std::endl;
	std::cout << p[5] << std::endl;

	int* ptr2 = p;
	std::cout << ptr2 << std::endl;
	void* ptr3 = p;
	std::cout << ptr3 << std::endl;

	std::cout << (p + 5) << std::endl;
	std::cout << (p + 5) - p << std::endl;
	std::cout << (p + 5) - 3 << std::endl;
	std::cout << (5 + p) << std::endl;

	std::cin.get();
}