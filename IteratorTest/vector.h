#pragma once

#include <initializer_list>

template <typename T>
class Vector;

template<typename T>
class VectorIterator : public std::iterator<std::input_iterator_tag, T>
{
	friend class Vector<T>;
private:
	VectorIterator(T* p) : p(p) {};
public:
	VectorIterator(const VectorIterator &it) : p(it.p) {}

	bool operator!=(VectorIterator const& other) const {
		return p != other.p;
	}
	bool operator==(VectorIterator const& other) const {
		return p == other.p;
	}
	T& operator*() const {
		return *p;
	}
	
	VectorIterator& operator++() {
		++p;
		return *this;
	}

private:
	T* p;
};

template <typename T>
class Vector
{
public:
	explicit Vector();
	explicit Vector(std::initializer_list<T> list);
	explicit Vector(const Vector& other);
	explicit Vector(Vector&& other);

	Vector& operator=(const Vector& other) {
		if (this != other)
		{
			if (data)
				delete[] data;
			data = new T[other.size()];
			for (size_t i = 0; i < other.size(); i++)
				this->data[i] = other.data[i];
			this->_size = other.size();
		}
	};
	Vector& operator=(Vector&& other){
		this->_size = other.size();
		this->data = other.data;
		other._size = 0;
		other.data = nullptr;
	}

	virtual ~Vector();

	void push_back(T&& t);
	void push_back(const T& t);
	void clear() { 
		delete[] data;
		data = nullptr;
		_size = 0;
	}

	size_t size() { return _size; }
	T* rawData() { return data; }

	VectorIterator<T> begin() { return VectorIterator<T>(data); }
	VectorIterator<T> end() { return VectorIterator<T>(data + _size); }

private:
	T* data;
	size_t _size;
};

template <typename T>
Vector<T>::Vector(): data(nullptr), _size(0){

}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list) : data(nullptr), _size(0) {
	for (auto i = list.begin(); i != list.end(); i++)
		this->push_back(std::move(*i));
}

template <typename T>
Vector<T>::Vector(const Vector& other){
	this->data = new T[other._size];
	for (size_t i = 0; i < other._size; i++)
		this->data[i] = other.data[i];
	this->_size = other._size;
}


template <typename T>
Vector<T>::Vector(Vector&& other) : data(nullptr), _size(0) {
	this->_size = other.size();
	this->data = other.data;
	other._size = 0;
	other.data = nullptr;
}

template <typename T>
Vector<T>::~Vector(){

}

template<typename T>
void Vector<T>::push_back(T && t){
	T* newData = new T[_size + 1];
	for (size_t i = 0; i < _size; i++)
		newData[i] = data[i];
	newData[_size] = std::move(t);
	this->_size = _size + 1;
}

template<typename T>
void Vector<T>::push_back(const T& t){
	T* newData = new T[_size + 1];
	for (size_t i = 0; i < _size; i++)
		newData[i] = data[i];
	newData[_size] = t;
	delete[] data;
	data = newData;
	this->_size = _size + 1;
}