// #include <ql/config.ansi.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

class Base 
{
    private:
    int x, x0;
    
    public:
    Base(): x(0) {}
    Base(int x_): x(x_), x0(x_) {}
    ~Base() {}
    int getX0() {return x0;}
    int getX() {return x;}
};

class Derived : public Base
{
    private:
    int y, y0;

    public:
    Derived(): y(0) {}
    Derived(int y_): y(y_), Base(y_) {}
    Derived(int x_, int y_): y(y_), Base(x_), y0(x_+y_) {}
    ~Derived() {}
    int getY0() {return y0;}
};

int main() {
    std::cout << "Hello World.\n";
    int a = 3;
    int& b = a;
    int&&c = std::move(a);
    b = 5;
    std::cout << a << ", " << b << ", " << c << "\n";
    c = 6;
    std::cout << a << ", " << b << ", " << c << "\n";

    Derived x(1, 2), y(3);
    Base z(static_cast<Base> (y));    
    // std::cout << x.x << ", " << x.y << ", " << x.getX0() << ", " << x.getY0() << std::endl;
    // std::cout << y.x << ", " << y.y << ", " << y.getY0() << std::endl;
    std::cout << x.getX0() << ", " << x.getY0() << std::endl;
    std::cout << y.getY0() << std::endl;
    std::cout << z.getX() << ", " << z.getX0() << ", " << std::endl;

    std::vector<int> v{2,3,4};
    auto found{ std::find(v.begin(), v.end(), 3) };



}