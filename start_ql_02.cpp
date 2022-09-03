#include <iostream>
#include <utility>

void reference(int& v) {
	std::cout << "left value reference" << std::endl;
}

void reference(int&& v) {
	std::cout << "right value reference" << std::endl;
}

void pass(int&& v) {
	std::cout << "pass by value: ";
	reference(v);
	std::cout << "pass by std::move: ";
	reference(std::move(v));
	std::cout << "pass by std::forward: ";
	reference(std::forward<int>(v));
	std::cout << "pass by static_cast<int&&>: ";
	reference(static_cast<int&&>(v));
}

void pass(int& v) {
	std::cout << "pass by value: ";
	reference(v);
	std::cout << "pass by std::move: ";
	reference(std::move(v));
	std::cout << "pass by std::forward: ";
	reference(std::forward<int>(v));
	std::cout << "pass by static_cast<int&&>: ";
	reference(static_cast<int&&>(v));
}
int main() {
	std::cout << "Hello World" << std::endl;
	std::cout << "Pass r value: \n";
	pass(1); 

	int a = 1;
	std::cout << "Pass l value: \n";
	pass(a); 
}