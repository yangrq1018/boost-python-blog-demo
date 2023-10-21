from mymath import add
from student import Student
from inc import IncBase, callInc


def test_add():
    assert add(2, 3) == 5
    assert add(1, 9) == 10
    assert add("a", "b") == "ab"
    assert add("hello, ", "world") == "hello, world"


def test_student_make():
    s = Student()
    assert s.name == "foo"


def test_py_override():
    class MyInc(IncBase):
        def inc(self, n):
            return n + 1
    f = MyInc()
    assert callInc(f, 3) == 4
    assert callInc(f, -1) == 0


def test_student_iter():
    s = Student()
    assert list(s) == ["bar", "baz"]
    s.makeFriend(Student("qux", 80))
    assert list(s) == ["bar", "baz", "qux"]


def test_student_add():
    s1 = Student("foo", 20)
    s2 = Student("qux", 80)
    assert (s1 + s2).name == "foo-qux"
    assert (s1 + s2).score == 100
