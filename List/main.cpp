#include <iostream>
#include "list.h"
#include <string.h>

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
	{
		List<int> l;
		test(l.size(), 0);
		test(l.empty(), true);
		l.push_back(20);
		List<int>::iterator it = l.begin();
		l.insert(it, 666, 2);
		test(*it, 20);
		l.push_front(30);
		it = l.begin();
		test(*it, 30);
		l.push_back(7);
		it = --l.end();
		test(*it, 7);
		test(l.size(), 5);
		it--;
		test(*it, 20);
		it = l.erase(it);
		test(*it, 7);
		l.erase(l.begin(), l.end());
		test(l.empty(), true);
	}
	{
		List<string> l;
		string t = "abra";
		l.push_front(t);
		l.push_front("cadabra");
		test(l.size(), 2);
		List<string>::iterator it = l.end();
		it--;
		test((*it).compare(t), 0);
		it = l.begin();
		test((*(it++)).compare("cadabra"), 0);
	}
	print_result();
}