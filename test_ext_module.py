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
