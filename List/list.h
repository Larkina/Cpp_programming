#ifndef LIST
#define LIST

#include <iostream>

template<typename T>
class List
{
private:
	class elem{
		friend class List<T>;
		T data;
		elem *next, *prev;
		elem(): next(NULL), prev(NULL), data(T()){};
		elem(elem* p, elem* n, const T d): prev(p), next(n), data(d){};
	};

	int i_size;
	elem *bf, *pr;

public:
	class iterator {
		friend class List<T>;
		elem* e;

		void shift(int count){
			for(int i = 0; i < count; ++i)
				if (e->next != NULL)
					(*this)++;
			for(int i = 0; i > count; ++count)
				if (e->prev != NULL)
					(*this)--;
		}

	public:
		iterator(): e(NULL){}; 
		iterator(const iterator& it): e(it.e){};
		iterator(elem* el): e(el){};

		T& operator*(){
			return this->e->data;
		}

		iterator& operator++(){
			this->e = this->e->next;
			return *this;	
		}

		iterator operator++(int){
			iterator tmp = iterator(*this);
			this->e = this->e->next;
			return tmp;
		}

		iterator& operator--(){
			this->e = this->e->prev;
			return *this;	
		}

		iterator operator--(int){
			iterator tmp = iterator(*this);
			this->e = this->e->prev;
			return tmp;	
		}

		bool operator==(const iterator& it){
			return it.e == e;
		}

		bool operator!=(const iterator& it){
			return it.e != e;
		}
	};

	List();
	~List();
	List(const List<T>& t);

	friend class iterator;

	iterator begin() const;
	iterator end() const;
	int size() const;
	bool empty() const;
	
	bool operator==(List<T>& t) const;
	List<T>& operator=(const List<T>& t);
	void insert(iterator pos, const T& data = T(), int count = 1);
	void push_back(const T& data);
	void push_front(const T& data);
	void pop_back();
	void pop_front();
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	T& front();
	T& back();
	void clear();
	void resize(int len, T val = T());
	friend std::ostream& operator<<(std::ostream& s, const List<T>& l);
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
	iterator it = iterator();
	it.e = this->bf->next;
	return it;
}

template<typename T>
typename List<T>::iterator List<T>::end() const{
	iterator it = iterator();
	it.e = this->pr;
	return it;	
}

template<typename T>
List<T>::~List(){
	elem *e = this->bf, *t = NULL;
	while (e != this->pr){
		t = e->next;
		delete e;
		e = t;
	}
	delete e;
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
		elem *e = new elem(it.e->prev, it.e, data);
		it.e->prev->next = e;
		it.e->prev = e;
		it.e = e;
		i_size++;
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

template<typename T>
typename List<T>::iterator List<T>::erase(iterator iter){
	return erase(iter, ++(*(new iterator(iter))));
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator first, iterator last){
	iterator it = first;
	while(it != last){
		elem *l = it.e->prev, *r = it.e->next;
		l->next = r;
		r->prev = l;
		delete it.e;
		it.e = r;
		i_size--;
	}
	return last;
}

template<typename T>
bool List<T>::operator==(List<T>& arg) const{
	if (arg.size() != i_size)
		return 0;
	iterator it1 = begin(), it2 = arg.begin();
	while(it1!= end() && *it1 == *it2){
		++it1;
		++it2;
	}
	return it1 == end();
}

template<typename T>
std::ostream& operator<<(std::ostream& s, List<T> l){
	for(List<int>::iterator i = l.begin(); i != l.end(); ++i)
		s << *i << " ";
	s << endl;	
	return s;
}

template<typename T>
void List<T>::pop_front(){
	erase(begin());
}

template<typename T>
void List<T>::pop_back(){
	erase(--end());
}

template<typename T>
T& List<T>::front(){
	return (bf->next->data);
}

template<typename T>
T& List<T>::back(){
	return (pr->prev->data);
}

template<typename T>
void List<T>::clear(){
	erase(begin(), end());
}

template<typename T>
void List<T>::resize(int len, T val = T()){
	if (len == i_size)
		return;
	if (len < i_size){
		iterator it = begin();
		it.shift(i_size - len + 1);
		erase(it, end());
	}
	else{
		for(int i = i_size; i < len; ++i)
			push_back(val);
	}
}

template<typename T>
typename List<T>& List<T>::operator=(const List<T>& t){
	clear();
	for(iterator it = t.begin(); it != t.end(); ++it)
		push_back(*it);
	return *this;
}

template<typename T>
List<T>::List(const List<T>& t){
	this->bf = new elem;
	this->pr = new elem;
	this->i_size = 0;
	this->bf->next = this->pr;
	this->bf->prev = NULL;
	this->pr->next = NULL;
	this->pr->prev = this->bf;
	*this = t;
}

#endif