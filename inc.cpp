#include <boost/python.hpp>

using namespace boost::python;

class IncBase {
public:
    virtual int inc(int n) = 0;

    int callInc(int n) {
        return inc(n);
    }
};

class IncBaseWrap: public IncBase, public wrapper<IncBase> {
public:
    int inc(int n) {
        // calls python override
        return this->get_override("inc")(n);
    }
};


BOOST_PYTHON_MODULE(inc) {
    class_<IncBaseWrap, boost::noncopyable>("IncBase")
    .def(init<>())
    .def("callInc", &IncBase::callInc)
    ;
}
