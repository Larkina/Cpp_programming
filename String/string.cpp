#include "m_string.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

String::String(){
	buff = NULL;
}

String::String(const char *s){
	buff = (char*)malloc(sizeof(s));
	strcpy(buff, s);
}

String::~String(){
//	free(buff);
}

String::String(const String &s){
	buff = (char*)malloc(sizeof(s.c_str()));
	strcpy(buff, s.c_str());
}

const char* String::c_str() const{
	return buff;
}

int String::length() const{
	return strlen(buff);
}

String& String::operator=(const String &s){
	buff = (char*)realloc(buff, sizeof(s.c_str()));
	strcpy(buff, s.c_str());
	return *this;
}

bool String::operator ==(const String &s){
	return strcmp(buff, s.c_str()) == 0;
}

bool String::operator !=(const String &s){
	return strcmp(buff, s.c_str()) != 0;
}

bool String::operator<(const String& s){
	return length() == s.length() ? strcmp(buff, s.c_str()) < 0 : length() < s.length();
}

bool String::operator<=(const String& s){
	return length() == s.length() ? strcmp(buff, s.c_str()) <= 0 : length() <= s.length();
}

bool String::operator>(const String& s){
	return length() == s.length() ? strcmp(buff, s.c_str()) > 0 : length() > s.length();
}

bool String::operator>=(const String& s){
	return length() == s.length() ? strcmp(buff, s.c_str()) >= 0 : length() > s.length();
}

String& operator+(String& a, String& b){
	char* t = (char*)malloc(sizeof(char) *(a.length() + 1));
	memset(t, 0, (a.length() + 1) * sizeof(char));
	memcpy(t, a.c_str(),  sizeof(char) * a.length());
	strcat(t, b.c_str());	
	String* s = new String(t);
	return *s;
}

String& operator+=(String& a, String& b){
	return a = a + b;
}

String& operator+=(String& a, char* b){
	return a = a + String(b);
}

String& operator+(String& a, char* b){
	return a + String(b);
}

String& operator+(char* a, String& b){
	return String(a) + b;
}

char String::operator[](int idx){
	return idx > 0 && idx < length() ? (c_str()[idx]) : NULL;
}

String& String::substr(int idx, int len){
	char* t = (char*)malloc(sizeof(char) * (len + 1));
	memset(t, 0, (len + 1) * sizeof(char));
	strncpy(t, buff + idx, len);
	String* s = new String(t);
	free(t);
	return *s;
}

ostream& operator<<(ostream& st, const String& s){
	return st << s.c_str();
}
istream& operator>>(istream& st, String& s){
	string t;
	st >> t;
	s = t.c_str();
	return st;
}