#include "Vector.h"
#include <iostream>

using namespace std;

Vector::Vector(const Value* rawArray, const size_t size, float coef ) {
    _size = size;
    _multiplicativeCoef = coef;
    _capacity = size;
    _data = new Value[_size];
    for(size_t i = 0; i < _size; i++){
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other) { 
    _size = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;
    _data = new Value[other._size];
    _capacity = other._size;
    for(size_t i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
	_size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        for(size_t i = 0; i < other._size; i++){
            _data[i] = other._data[i];
	}
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
        other._size = 0;
	other._capacity = 0;
        other._multiplicativeCoef = 0;
        other._data = nullptr;
    }
    return *this;
}

Vector::~Vector() {
	delete[] _data;
}

void Vector::pushBack(const Value& value) {
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    _data[_size - 1] = value;
}
	

void Vector::pushFront(const Value& value) {
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    _data[0] = value;
    for (size_t i = 1; i < _size; i++) {
        _data[i] = _data[i+1];
    }
}

void Vector::insert(const Value& value, size_t pos) {
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < pos; ++i) {
        result[i] = _data[i];
    }
    result[pos] = value;
    for(size_t j = pos + 1; j <_size; j++ ) {
        result[j] = _data[j-1];
    }
    delete[] _data;
    _data = result;
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    _size += size;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < pos; i++) {
        result[i] = _data[i];
    }
    for (size_t j = 0; j < size; j++) {
        result[pos + j] = values[j];
    }
    for (size_t k = pos + size; k < _size; k++) {
        result[k] = _data[k - size];
    }
    delete[] _data;
    _data = result;
}

void Vector::insert(const Vector& vector, size_t pos) {
    this->insert(vector._data, vector._size, pos);
}

void Vector::popBack(){
    if( _size > 0) {
        _size = _size - 1;
    }
    else {
	    throw out_of_range("size = 0");
    }
}

void Vector::popFront() {
    erase(0, 1);
}

void Vector::erase(size_t pos, size_t count){
    if (_size == 0) {
        throw out_of_range("_size = 0");
    }
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    if(pos + count >= _size) {
        count = _size - pos;
    }
    for (size_t i = pos + count; i < _size; i++) {
        _data[i - count] = _data[i];
    }
    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    if ((_data == nullptr) || (_capacity == 0)) {
	_capacity = _multiplicativeCoef;
        _data = new Value[_capacity];
    }
    for (size_t i = 0; i < (endPos - beginPos); i++) {
		    for (size_t j = beginPos + 1; j < _size; j++) {
   			    _data[j - 1] = _data[j];
    	  }
    _size--;
	  }
}

size_t Vector::size() const{
    return _size;
};

size_t Vector::capacity() const{
    return _capacity;
}

 double Vector::loadFactor() const{
     return (double)_size / (double)_capacity;
 }

Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const{
    return _data[idx];
}

long long Vector::find(const Value& value) const{
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
	    return i;
	}
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity > _capacity) {
        Value* result = new Value[capacity];
	if (_data != nullptr) {
            for (size_t i = 0; i < _size; i++) {
                result[i] =  _data[i];
            }
            delete[] _data;
	}
        _data = result;
	_capacity = capacity;
    }
}

void Vector::shrinkToFit() {
    if(_capacity > _size) {
        _capacity = _size;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < _size; i++) { 
        result[i] = _data[i];
    }
    delete[] _data;
    _data = result;   
}

Vector::Iterator::Iterator(Value* ptr) {
    _ptr = ptr;
}

Value& Vector::Iterator::operator*() {
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const {
    return *_ptr;
}

Value* Vector::Iterator::operator->(){
    return _ptr;
}

const Value* Vector::Iterator::operator->() const {
    return _ptr;
}
    
Vector::Iterator Vector::Iterator::operator++() {
    _ptr++;
    return *this;
}
    
Vector::Iterator  Vector::Iterator::operator++(int) {
    Vector::Iterator oldValue(*this);
    ++(*this);
    return oldValue;
}
    
bool Vector::Iterator::operator==(const Iterator& other) const {
    return _ptr == other._ptr;
}
    
bool Vector::Iterator::operator!=(const Iterator& other) const {
    return !(_ptr == other._ptr);
}

Vector::Iterator Vector::begin() {
    Vector::Iterator head(_data);
    return head;
}

Vector::Iterator   Vector::end() {
    Vector::Iterator tail(_data + _size);
    return tail;
}
