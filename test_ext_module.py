import pytest
from mymath import add
from student import Student


def test_add():
    assert add(2, 3) == 5
    assert add(1, 9) == 10
    assert add("a", "b") == "ab"
    assert add("hello, ", "world") == "hello, world"


def test_student_make():
    s = Student()
    assert s.name == "foo"


def test_py_override():
    from inc import IncBase, callInc, __IncBase

    class MyInc1(__IncBase):
        def inc(self, n):
            return n + 1
    with pytest.raises(RuntimeError):
        f = MyInc1()

    class MyInc2(IncBase):
        def inc(self, n):
            return n + 1
    f = MyInc2()
    assert callInc(f, 3) == 4
    assert callInc(f, -1) == 0


def test_cpp_override():
    from inc import IncImp, callInc
    f = IncImp()
    assert callInc(f, 3) == 4


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
