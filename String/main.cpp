#include <iostream>
#include <string>
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
	cout << tests_count - correct << " - failed " << endl;
	if (tests_count == correct)
		cout << "Solution Accepted" << endl;
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
	// link count 
	{
			String a = "abc";
		{
			String b = a;
			String с = b, d = a;
		}
		test(a.get_link_count(), 1);
		{
			String b = a;
			String c = a + b;
			test(c.get_link_count(), 1);
			test(a.get_link_count(), 2);
		}
		{
			String b = "abba";
			b += "Test";
			test(b.get_link_count(), 1);
		}
		{
			String b = a;
			b += b;
			test(b.get_link_count(), 1);
		}
		// proxy char
		a[0] = "L";
		test(strcmp(a.c_str(), "Lbc"), 0);
		{	
			String b = a, c = a, t = a;
			b[2] = "D";
			c[1] = "S";
			t[1] = "SD";
			String h = str;
			test(a.get_link_count(),t.get_link_count());
			h[0] = "unbelievable";
			test(strcmp(c.c_str(), "LSc"), 0);
			test(strcmp(b.c_str(), "LbD"), 0);	
			test(strcmp(t.c_str(), "LSD"), 0);
			test(strcmp(h.c_str(), "unbelievable"), 0);
		}
		// operator char()
		{
			char d = String("Fascinating")[2];
			test(d, 's');
		}
		// = char
		{
			String d = "Test";
			d[0] = 'R';
			test(strcmp(d.c_str(), "Rest"), 0);
		}
		{
			String d = "Past ", b = "Rear";
			String c = d, f = d;
			d = d + b;
			test(f.get_link_count(), 2);
			test(d.get_link_count(), 1);
		}
		{
			String d = "Before";
			String c = d, f = d, j = d;
			d.insert(" First", 5);
			test(c.get_link_count(), 3);
			test(d.get_link_count(), 1);
		}
		{
			String d = "Misheard";
			String c = d, f = d, j = d;
			d.delete_substr(4, 5);
			test(c.get_link_count(), 3);
			test(d.get_link_count(), 1);
		}
	}
	// Старые

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
	String tmp = String("T_T") + String(" >_<");
	test(strcmp(tmp.c_str(), "T_T >_<"), 0);

	// [], substr
	String x("Cat");
	x[0] = "N";
	test(strcmp(x.c_str(), "Nat"), 0);
	char tt = r[3];
	test(tt, 'b');
	tt = tmp[1];
	test(tt, '_');
	test(strcmp(tmp.substr(0, 3).c_str(), "T_T"), 0);
	test(strcmp(tmp.substr(4, 3).c_str(), ">_<"), 0);
	
	//insert delete
	
	tmp.insert("O_o ", 3);
	test(strcmp(tmp.c_str(), "T_T O_o >_<"), 0);
	t.delete_substr(2, 3);
	test(strcmp(t.c_str(), "Abca"), 0);

	String k, n("To "), m("or ");
	k = n + "be " + m + "not " + n  + "be?";
	test(strcmp(k.c_str(), "To be or not To be?"), 0);
	print_result();
}