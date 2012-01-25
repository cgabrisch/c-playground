#include "strutils.h"
#include "unittest.h"

void test_strindex(void) {
	ut_equals(3, strindex("abcdef", "de"));
	ut_equals(4, strindex("abcddef", "de"));
	ut_equals(3, strindex("abcdedef", "de"));
	ut_equals(3, strindex("abcdef", "def"));
	ut_equals(-1, strindex("abcdef", "defg"));
	ut_equals(-1, strindex("abcdef", "deg"));
	ut_equals(3, strindex("abcdef", "d"));
	ut_equals(0, strindex("abcdef", "abc"));
	ut_equals(0, strindex("abcdef", ""));
	ut_equals(-1, strindex("abcdef", "h"));
	ut_equals(-1, strindex("abcdef", "habc"));
	ut_equals(-1, strindex("abcdef", "abcdefg"));
	ut_equals(-1, strindex("", "d"));
}

void test_strrindex(void) {
	ut_equals(2, strrindex("abc", "c"));
	ut_equals(0, strrindex("abc", "abc"));
	ut_equals(-1, strrindex("abc", "d"));
	ut_equals(-1, strrindex("abc", "cbc"));
	ut_equals(5, strrindex("abcabc", "c"));
	ut_equals(3, strrindex("abcabc", "ab"));
	ut_equals(-1, strrindex("abc", "dabc"));
	ut_equals(-1, strrindex("", "abc"));
	ut_equals(3, strrindex("abc", ""));
}

int main(int argc, char ** args) 
{
	ut_testfunction(test_strindex);
	ut_testfunction(test_strrindex);

	return 0;
}
