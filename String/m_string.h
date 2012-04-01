#ifndef STRING
#define STRING

#include <istream>
#include <ostream>
#include <iostream>
#include <algorithm>

class String {
	class Buffer{
	public:
		char* str;
		int link_count;
		int len;
		
		Buffer(): link_count(0), len(0){};
		void check_link(){
			if (link_count == 0)
				free(str);
		}
	};

	class proxy_char{
		String& parent;
		int idx;
	public:
		proxy_char(int i, String& s): idx(i), parent(s){};
		proxy_char& operator=(char* t){
			if(--parent.buff->link_count){
				char* new_value = (char*)malloc(sizeof(char) * (parent.length() + 1));
				strcpy(new_value, parent.buff->str);
				parent.buff = new Buffer();
				parent.buff->str = new_value;
				parent.buff->len = strlen(new_value);
			}
			parent.buff->link_count = 1;
			int l = strlen(t) > parent.length() + 1? parent.length() + 1 : strlen(t);
			parent = parent.substr(0, idx) + t + parent.substr(idx + l, parent.length() - l + 1);
			return *this;
		}
		operator char(){
			return parent.buff->str[idx];
		}
	};
	
	friend class proxy_char;
	Buffer* buff;

public:

	String(const char* s = "");
	String(const String& s);
	~String();
	
	const char* c_str() const;
	int length() const;

	String& operator=(const String& s);

	int get_link_count()const {
		return buff->link_count;
	}

	bool operator==( const String& s);
	bool operator!=( const String& s);
	bool operator<(const String& s);
	bool operator<=(const String& s);
	bool operator>(const String& s);
	bool operator>=(const String& s);

	proxy_char operator[](int idx);
	String substr(int idx, int len) const;
	void insert(char* s, int idx);
	void delete_substr(int idx, int len);

	friend String operator+(const String& a, const String& b);
	friend String& operator+=(String& a, const String& b);

	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);
};

#endif