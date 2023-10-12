#include <boost/python.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::python;
using std::ostream;
using std::string;
using std::vector;

class Student {
public:
    Student() : m_name("foo"), m_score(100) {
        initFriends();
    }
    Student(const string &name, int64_t score) : m_name(name), m_score(score) {
        initFriends();
    }
    ~Student() {}
    string name() const {
        return m_name;
    }
    void set_name(const string &name) {
        m_name = name;
    }
    int64_t score() const {
        return m_score;
    }
    void learn() {
        m_score++;
    }
    typedef vector<string>::const_iterator const_iterator;
    const_iterator begin() const {
        return m_friends.begin();
    }
    const_iterator end() const {
        return m_friends.end();
    }
    void makeFriend(const Student &s) {
        m_friends.push_back(s.name());
    }

private:
    string m_name;
    uint64_t m_score;
    vector<string> m_friends;

    void initFriends() {
        m_friends.push_back("bar");
        m_friends.push_back("baz");
    }
};

// operator overloads
ostream &operator<<(ostream &os, const Student &s) {
    os << "Student: " << s.name() << ", " << s.score();
    return os;
}

Student operator+(const Student &a, const Student &b) {
    return Student(a.name() + "-" + b.name(), a.score() + b.score());
}

BOOST_PYTHON_MODULE(student) {
    class_<Student>("Student", "Represent a student", init<>())
      .def(init<const string &, int64_t>())
      .def(self_ns::str(self))
      .def(self_ns::repr(self))
      .def(self + self)
      .add_property("name", &Student::name, &Student::set_name)
      .add_property("score", &Student::score)
      .def("learn", &Student::learn, "gain some score")
      .def("makeFriend", &Student::makeFriend, "make a friend")
      .def("__iter__", iterator<const Student>());
}