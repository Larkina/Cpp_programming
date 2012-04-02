#ifndef LIST
#define LIST

#include <istream>
#include <ostream>
#include <iostream>

template<typename T>
class List{
private:
	class elem{
		friend class List<T>;
		T data;
		elem *next, *prev;
	};

	int i_size;
	elem *bf, *pr;

public:
	class iterator{

		List* h;
		elem* e;

		static iterator CreateIterator(List* h,  elem e){
			iterator it = new iterator;
			iter->e = e;
			iter->h = h;
			return *it;
		}
	public:
		~iterator();
		T operator*(){
			if (e != h->pr)
				return &(iter->e->data);
		}
		iterator& operator++(){
			if (iter->e != iter->h->pr)
				iter->e = iter->e->next;
			return iter;	
		}
		iterator& operator=(const iterator& it){
			*this->h = it.h;
			*this->e = it.e;
			return *this;
		}
		bool operator==(const iterator& it){
			return *this->h == it.h && it.e == *this->e;
		}
		bool operator!=(const iterator& it){
			return !(*this == it);
		}
	};

	List();
	~List();

	iterator begin() const;
	iterator end() const;
	int size() const;

};

template<typename T>
List<T>::List(){
	this->bf = new elem;
	this->pr = new elem;
	this->i_size = 0;
	this->bf->next = this->pr;
	this->bf->prev = NULL;
	this->pr->next = NULL;
	this->pr->prev = this->bf;
}

template<typename T>
typename List<T>::iterator List<T>::begin() const{
	return CreateIterator(*this, this->bf->next);
}

template<typename T>
typename List<T>::iterator List<T>::end() const{
	return CreateIterator(*this, this->pr->prev);
}

template<typename T>
List<T>::~List(){
	elem *e = this->bf, *t = NULL;
	while (e != this->pr){
		t = e->next;
		free(e);
		e = t;
	}
	free(e);
}

template<typename T>
int List<T>::size() const{
	return i_size;	
}

#endif