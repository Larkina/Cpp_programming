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
		T* data;
		elem *next, *prev;
		elem(){
			next = NULL;
			prev = NULL;
			data = NULL;
		}
		elem(elem* t){
			next = t->next;
			prev = t->prev;
			data = t->data == NULL ? NULL : new T(*t->data);
		}
	};

	int i_size;
	elem *bf, *pr;

public:
	class iterator{
		friend class List<T>;
		List& h;
		elem* e;

	public:
		iterator(): e(NULL), h(List<T>()){}; // да-да. конструктор на врмеенный элемент. замнем)
		iterator(const iterator& it): h(it.h){
			e = it.e;// и зачем это?
		}
		T operator*(){
			if (e->data != NULL)
				return *(this->e->data);
			else
				return NULL; // Но мы то знаем, что исключение
		}
		iterator& operator++(){
			if (this->e != this->h.pr)
				this->e = this->e->next;
			return *this;	
		}
		iterator& operator++(int){
			iterator *tmp = new iterator();
			tmp->e = new elem(this->e);
			if (this->e != this->h.pr)
				this->e = this->e->next;
			return *tmp;
		}
		iterator& operator--(){
			if (this->e != this->h.bf)
				this->e = this->e->prev;
			return *this;	
		}
		iterator& operator--(int){
			iterator *tmp = new iterator();
			tmp->e = new elem(this->e);
			if (this->e != this->h.bf)
				this->e = this->e->prev;
			return *tmp;	
		}
		iterator& operator=(const iterator& it){
			this->h = it.h;
			this->e = it.e;
			return *this;
		}
		bool operator==(const iterator& it){
			return it.e == e;
		}
		bool operator!=(const iterator& it){
			return !(*this == it);
		}
	};

	List();
	~List();
	
	friend class iterator;

	iterator begin() const;
	iterator end() const;
	int size() const;
	bool empty() const;
	
	bool operator==(List<T>& t) const;

	void insert(iterator pos, const T& data = T(), int count = 1);
	void push_back(const T& data);
	void push_front(const T& data);
	void pop_back();
	void pop_front();
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);

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
	iterator *it = new iterator();
	it->e = this->bf->next;
	it->h = *this;
	return *it;
}

template<typename T>
typename List<T>::iterator List<T>::end() const{
	iterator *it = new iterator();
	it->e = this->pr;
	it->h = *this;
	return *it;	
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
		e->data = new T(data);
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
	if (first.h.empty())
		return last;
	iterator it = first;
	while(it != last){
		elem *l = NULL, *r = NULL;
		l = it.e->prev;
		r = it.e->next;
		l->next = r;
		r->prev = l;
		free(it.e);
		it.e = r;
		i_size--;
	}
	return it;
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

template<typename T> // wtf?
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

#endif