#include <boost/python.hpp>

using namespace boost::python;

class IncBase {
public:
    virtual int inc(int n) = 0;
};

class IncImp : public IncBase {
public:
    int inc(int n) override {
        return n + 1;
    }
};

int callInc(IncBase& i, int n) {
    return i.inc(n);
}

class IncBaseWrap : public IncBase, public wrapper<IncBase> {
public:
    int inc(int n) override {
        // calls python override
        return this->get_override("inc")(n);
    }
};

BOOST_PYTHON_MODULE(inc) {
    // clang-format off
    class_<IncBaseWrap, boost::noncopyable>("IncBase")
        .def(init<>());
    class_<IncImp, bases<IncBase>, boost::noncopyable>("IncImp")
        .def(init<>());
    def("callInc", callInc, (arg("imp"), arg("n")));
    // clang-format on
}
