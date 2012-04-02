#include <iostream>
#include "list.h"

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

int main(){
	List<int> l;
	test(l.size(), 0);
	print_result();
}