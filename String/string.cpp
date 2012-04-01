#include "m_string.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

String::String(const char *s){
	int l = strlen(s);
	buff = new Buffer();
	buff->str = (char*)malloc(sizeof(char) * (l + 1));
	strcpy(buff->str, s);
	buff->len = l;
	buff->link_count++;
}

String::~String(){
	buff->link_count--;
	//buff->check_link();
}

String::String(const String &s){
	buff = s.buff;
	buff->link_count++;
}

const char* String::c_str() const{
	return buff->str;
}

int String::length() const{
	return buff->len;
}

String& String::operator=(const String &s){
	buff->link_count--;
	buff->check_link();
	buff = s.buff;
	buff->link_count++;
	return *this;
}

bool String::operator ==(const String &s){
	return strcmp(buff->str, s.c_str()) == 0;
}

bool String::operator !=(const String &s){
	return strcmp(buff->str, s.c_str()) != 0;
}

bool String::operator<(const String& s){
	return buff->len == s.length() ? strcmp(buff->str, s.c_str()) < 0 : buff->len < s.length();
}

bool String::operator<=(const String& s){
	return buff->len == s.length() ? strcmp(buff->str, s.c_str()) <= 0 : buff->len <= s.length();
}

bool String::operator>(const String& s){
	return buff->len == s.length() ? strcmp(buff->str, s.c_str()) > 0 : buff->len > s.length();
}

bool String::operator>=(const String& s){
	return buff->len == s.length() ? strcmp(buff->str, s.c_str()) >= 0 : buff->len > s.length();
}

String operator+(const String& a, const String& b){
	char* t = (char*)malloc(sizeof(char) *(a.length() + b.length() + 1));
	memcpy(t, a.c_str(),  sizeof(char) * (a.length() + 1));
	strcat(t, b.c_str());	
	String s(t);
	free(t);
	return s;
}

String& operator+=(String& a, const String& b){
	return a = a + b;
}

 String::proxy_char String::operator[](int idx){
	return proxy_char(idx, *this);
}

String String::substr(int idx, int len) const{
	char* t = (char*)malloc(sizeof(char) * (len + 1));
	memset(t, 0, (len + 1) * sizeof(char));
	strncpy(t, buff->str + idx, len);
	String s(t);
	free(t);
	return s;
}

void String::insert(char* s, int idx){
	char* t = (char*)malloc(sizeof(char) * (length() - idx + 1));
	strncpy(t, buff->str + idx + 1, sizeof(char) * (length() - idx + 1));
	buff->str = (char*)realloc(buff->str, sizeof(char) * (strlen(s) + buff->len + 1)); 
	memset(buff->str + idx + 1, 0, sizeof(char) * (idx + 1));
	strcat(buff->str, s);
	strcat(buff->str, t);
	free(t);
}

void String::delete_substr(int idx, int len){
	char* t = (char*)malloc(sizeof(char) * (length() - len + 1));
	strncpy(t, buff->str + idx + len, sizeof(char) * (length()- len + 1));
	buff->str = (char*)realloc(buff->str, sizeof(char) * (idx + 1)); 
	memset(buff->str + idx, 0, sizeof(char) * (idx + 1));
	strcat(buff->str, t);
	free(t);
}

ostream& operator<<(ostream& st, const String& s){
	return st << s.c_str();
}
istream& operator>>(istream& st, String& s){
	int size = 5;
	char* t = (char*) malloc(sizeof(char) * (size + 1));
	while (1){
		st.getline(t, size);
		s += t;
		if (strlen(t) != size)
			break;
	}
	free(t);
	return st;
}