#include <iostream>
#include "m_string.h"

using namespace std;

#define test(a, b) m_test(a, b, __LINE__)

int tests_count = 0, correct = 0;

void print_msg_and_inc_tests_count(bool res, int line){
	tests_count++;
	correct += res;
	cout << "Test: " << tests_count << (res ? " OK   " : " FAIL ") 
		 << " at line: " << line << endl;
}

void print_result(){
	cout << correct << " - PASSED " << endl;
	cout << tests_count - correct << " - FAILED " << endl;
	int t;
	cin >> t;
}

template <typename T>
void m_test(T get, T res, int line){
	print_msg_and_inc_tests_count(get == res, line);
}

const
	char* str = "Ababaca";

int main(){
	// Конструкторы + c_str
	String t(str);
	cout << strcmp(t.c_str(), str) << endl;
	test(strcmp(t.c_str(), str), 0);
	String a(t);
	test(strcmp(a.c_str(), str), 0);

	// length
	String g = "xyz";
	test(t.length(), 7);
	test(g.length(), 3);

	// Сравнения
	String r = t;
	test(r != g, true);
	test(t == a, true);
	test(t > g, true);
	test(g < "xzz", true);
	test(t >= str, true);

	// +, += 
	test(strcmp((r + r).c_str(), "AbabacaAbabaca"), 0);
	test(strcmp((t + g).c_str(), "Ababacaxyz"), 0);
	r += "lol";
	test(strcmp(r.c_str(), "Ababacalol"), 0);
	test(strcmp((g + "cmp").c_str(), "xyzcmp"), 0);
	String tmp = "T_T" + String(" >_<");
	test(strcmp(tmp.c_str(), "T_T >_<"), 0);

	// [], substr
	test(r[3], 'b');
	test(tmp[1], '_');
	test(strcmp(tmp.substr(0, 3).c_str(), "T_T"), 0);
	test(strcmp(tmp.substr(4, 3).c_str(), ">_<"), 0);

	print_result();
}