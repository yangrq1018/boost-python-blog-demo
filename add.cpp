#include <boost/python.hpp>
#include <string>

using namespace boost::python;
using std::string;

int add(const int& a, const int& b) {
    return a+b;
}

string add(const string& a, const string& b) {
    return a+b;
}

int (*add1)(const int& a, const int& b) = add;
string (*add2)(const string& a, const string& b) = add;

BOOST_PYTHON_MODULE(mymath) {
    def("add", add1, (arg("a"), arg("b")));
    def("add", add2, (arg("a"), arg("b")));
}