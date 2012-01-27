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

void test_atof(void) {
	ut_equals_f(1.0, atof("1.0"),1e-10);
	ut_equals_f(1.5, atof("1.5"),1e-10);
	ut_equals_f(1.23, atof("1.23"),1e-10);
	ut_equals_f(-2.3, atof("-2.3"),1e-10);
	ut_equals_f(2.0, atof("2"),1e-10);
	ut_equals_f(123.0, atof("1.23e2"),1e-10);
	ut_equals_f(0.123, atof("1.23E-1"),1e-10);
	ut_equals_f(123.45e-6, atof("123.45e-6"),1e-10);
}

int main(int argc, char ** args) 
{
	ut_testfunction(test_strindex);
	ut_testfunction(test_strrindex);
	ut_testfunction(test_atof);
	
	return 0;
}

