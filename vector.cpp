#include "Vector.h"

Vector::Vector(const Value* rawArray, const size_t size, float coef ) {
    _size = size;
    _multiplicativeCoef = coef;
    _data = new Value[_size];
    for(size_t i = 0; i < _size; i++){
        _data[i] = rawArray[i];
    }

}

Vector::Vector(const Vector& other) { 
    size_t _size = other._size;
    size_t _capacity = other._capacity;
    _data = new Value[other._capacity];
    float  _multiplicativeCoef = other._multiplicativeCoef;
    for(size_t i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
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
    for(size_t i = 0; i < other._size; i++) {
        _data[i] = other._data[i];
    }
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) {
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;
        for(size_t i = 0; i < other._size; i++) {
            _data[i] = other._data[i];
        }
    other._data = nullptr;
    }
    return *this;
}

Vector::~Vector() {
	delete[] _data;
}

void Vector::pushBack(const Value& value) {
    if (_data == nullptr) {
        _data = new Value[_capacity];
    }
    _size++;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < _size; i++) {
        result[i] =  _data[i];
    }
    delete[] _data;
    _data = result;
    _data[_size - 1] = value;
}
	

void Vector::pushFront(const Value& value) {
    if (_data == nullptr) {
        _data = new Value[_capacity];
    }
    _size++;
    if (_size > _capacity) {
		    _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    result[0] = value;
    for (size_t i = 1; i < _size; i++) {
			  result[i] = _data[i-1];
		}
    delete[] _data;
    _data = result;    
}

void Vector::insert(const Value& value, size_t pos) {
    if (_data == nullptr) {
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
    if (_data == nullptr) {
        _data = new Value[_capacity];
    }
    _size += size;
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < _size; i++) {
        result[i] = _data[i];
    }
    delete[] _data;
    _data = result;
    for(size_t i = 0; i < size; i++){
        _data[pos + i] = values[i];
    }
}

void Vector::insert(const Vector& vector, size_t pos) {
    this->insert(vector._data, vector._size, pos);
}

void Vector::popBack(){
    _size = _size - 1;
}

void Vector::popFront(){
    if (_data == nullptr){
        _data = new Value[_capacity];
    }
    if (_size > _capacity) {
        _capacity = _capacity * _multiplicativeCoef;
    }
    Value* result = new Value[_capacity];
    for (size_t i = 0; i < _size - 1; ++i) {
        result[i] = _data[i + 1];
    }
    delete[] _data;
    _data = result;
    _size--;
}

void Vector::erase(size_t pos, size_t count){
    if (_data == nullptr) {
        _data = new Value[_capacity];
    }
    if(pos + count >= _size) {
        count = _size - pos;
    }
    for (size_t i = pos + count; i < _size; i++) {
        _data[i - count] = _data[i];
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos){
    if (_data == nullptr) {
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
     return (double)_size/_capacity;
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
        for (size_t i = 0; i < _size; i++) {
            result[i] =  _data[i];
        }
        delete[] _data;
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
        result[i] = result[i];
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
