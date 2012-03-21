#ifndef STRING
#define STRING

#include <istream>
#include <ostream>
#include <iostream>

class String {
	char* buff;

public:
	String();
	String(const char* s);
	String(const String& s);
	~String();
	
	const char* c_str() const;
	int length() const;

	String& operator=(const String& s);

	bool operator==( const String& s);
	bool operator!=( const String& s);
	bool operator<(const String& s);
	bool operator<=(const String& s);
	bool operator>(const String& s);
	bool operator>=(const String& s);

	char operator[](int idx);
	String& substr(int idx, int len);
	
	friend String& operator+(String& a, String& b);
	friend String& operator+(char* a, String& b);
	friend String& operator+(String& a, char* b);
	friend String& operator+=(String& a, String& b);
	friend String& operator+=(String& a, char* b);

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
};

#endif