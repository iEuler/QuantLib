#include <iostream>
#include <vector>
#include <string>

class myC {
public:
    friend std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec);
    friend std::ostream& operator<<(std::ostream& out, const std::vector<double>& vec);
};

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    out << "int type: \n";
    for (int i=0; i<vec.size(); ++i) out << vec[i] << ", ";
    out << "\n";
}

std::ostream& operator<<(std::ostream& out, const std::vector<double>& vec) {
    out << "double type: \n";
    for (int i=0; i<vec.size(); ++i) out << vec[i] << "; ";
    out << "\n";
}

namespace my {

class myC2 {
public:
    friend std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec);    
};

std::ostream& operator<<(std::ostream& out, const std::vector<int>& vec) {
    out << "int type in my namespace: \n";
    for (int i=0; i<vec.size(); ++i) out << vec[i] << ", ";
    out << "\n";
}

};


int main() {
    std::vector<int> v{5,6,7,3,4,2};
    std::cout<<v;
    std::string s = "hello world\n";
    std::cout<<s;
    std::vector<double> v2{5.5,6.2,7.1,3.8,4.6,2.7};
    std::cout<<v2;
    std::cout<<v;
    

}