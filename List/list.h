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
		friend class List<T>;
		List& h;
		elem* e;

		static iterator& CreateIterator(const List<T>& h, elem* e){
			iterator* it = new iterator();
			it->e = e;
			it->h = h;
			return *it;
		}
	public:
		iterator(): e(NULL), h(List<T>()){};
		//~iterator();
		T operator*(){
			if (e != h.pr)
				return this->e->data;
			else
				return T(); // Но мы то знаем, что исключение
		}
		iterator& operator++(){
			if (this->e != this->h.pr)
				this->e = this->e->next;
			return *this;	
		}
		iterator& operator--(){
			if (this->e != this->h.bf)
				this->e = this->e->prev;
			return *this;	
		}
		iterator& operator=(const iterator& it){
			this->h = it.h;
			this->e = it.e;
			return *this;
		}
		bool operator==(const iterator& it){
			return *this->h == it.h && it.e == *this->e;
		}
		bool operator!=(const iterator& it){
			return !(*this == it);
		}
	};

	//friend class iterator;
	List();
	~List();

	iterator begin() const;
	iterator end() const;
	int size() const;
	bool empty() const;

	void insert(iterator pos, const T& data = T(), int count = 1);
	void push_back(const T& data);
	void push_front(const T& data);

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
	return iterator::CreateIterator(*this, this->bf->next);
}

template<typename T>
typename List<T>::iterator List<T>::end() const{
	return iterator::CreateIterator(*this, this->pr);
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

template<typename T>
bool List<T>::empty() const{
	return i_size == 0;
}

template<typename T>
void List<T>::insert(iterator iter, const T& data = T(), int count = 1){
	iterator it = iter;
	for(int i = 0; i < count; ++i){
		elem *e = (elem*)malloc(sizeof(elem));
		e->next = it.e;
		e->prev = it.e->prev;
		e->data = data;
		it.e->prev->next = e;
		it.e->prev = e;
		it.e = e;
		it.h.i_size++;	
	}
}

template<typename T>
void List<T>::push_back(const T& data){
	iterator it = end();
	insert(it, data);
}

template<typename T>
void List<T>::push_front(const T& data){
	iterator it = begin();
	insert(it, data);
}

#endif