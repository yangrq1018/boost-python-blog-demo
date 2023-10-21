from mymath import add
from student import Student
from inc import IncBase

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
    assert f.callInc(3) == 4
    assert f.callInc(-1) == 0