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
    // the way to export an abstract type, only for declaration purpose
    // to make bases<IncBase> happy
    class_<IncBase, boost::noncopyable>("__IncBase", no_init);

    // Wrap inter python override call
    class_<IncBaseWrap, boost::noncopyable>("IncBase").def(init<>());

    // Implementation
    class_<IncImp, bases<IncBase>>("IncImp").def(init<>());

    // Consumer
    def("callInc", callInc, (arg("imp"), arg("n")));
}
