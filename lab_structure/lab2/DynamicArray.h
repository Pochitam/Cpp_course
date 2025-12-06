#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <cstdint>
#include <initializer_list>
#include <exception>
#include <iostream>
#include <stdexcept>

template<typename T>
class DynamicArray {
private:
  T* data;
  std::int64_t size = -1;
  std::int64_t capacity;

public:
  DynamicArray();
  DynamicArray(std::int64_t capacity);
  DynamicArray(DynamicArray& other);
  DynamicArray(std::initializer_list<T> arr);
  ~DynamicArray();

  void push_back(T x);
  T add(std::int64_t idx1, std::int64_t idx2);
  T max();
  T min();
  void clear();
  void reinitialize();
  void printData();
  void push_front(T x);
  T front();
  T back();
  void insert(std::int64_t ind, T val);
  void remove(std::int64_t ind);
  void erase_after(std::int64_t ind);
  void increase_capacity(std::int64_t newCap);
  void decrease_capacity(std::int64_t newCap);
  bool isEmpty();
  int len();
  int limit();

  T operator[](std::int64_t ind);
  T operator()();
  DynamicArray operator+(const DynamicArray& other);
  DynamicArray& operator=(const std::initializer_list<T> other);
  DynamicArray& operator=(const DynamicArray& other);
  DynamicArray& operator+=(std::initializer_list<T> other);
  DynamicArray& operator+=(DynamicArray& other);


};

template<typename T>
DynamicArray<T>::DynamicArray() {
  this->capacity = 8;
  this->data = new T[this->capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(std::int64_t capacity) {
  if (capacity < 1) {
    throw std::invalid_argument("stupid user");
  }
  this->capacity = capacity;
  this->data = new T[this->capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray& other) {
  this->size = other.size;
  this->capacity = other.capacity;
  this->data = new T[this->capacity];

  for (int i = 0; i <= size; ++i) {
    this->data[i] = other.data[i];
  }
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> arr){
  capacity = arr.size()*2;
  size = arr.size()-1;
  data = new T[capacity];

  int i=0;
  for (const T& el:arr){
    data[i++] = el;
  }
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
  if (this->data) {
    delete[] this->data;
  }
}

template<typename T>
bool DynamicArray<T>::isEmpty(){
    return size==-1;
}

template<typename T>
int DynamicArray<T>::len(){
    return size+1;
}

template<typename T>
int DynamicArray<T>::limit(){
    return capacity;
}

template<typename T>
void DynamicArray<T>::push_back(T x) {
  if (size + 1 >= capacity) {
    std::int64_t newCapacity = capacity * 2;
    T* tempArray = new T[newCapacity];
    for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  data[++size] = x;
}

template<typename T>
T DynamicArray<T>::add(std::int64_t idx1, std::int64_t idx2) {
  if (idx1 > size || idx2 > size || idx1 < 0 || idx2 < 0) {
    throw std::invalid_argument("idx1 or idx2 out of range");
  }
  return data[idx1] + data[idx2];
}

template<typename T>
T DynamicArray<T>::max() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  float currentMax = -1e+38;
  for (int i = 0; i <= size; ++i) {
    if (data[i] >= currentMax) {
      currentMax = data[i];
    }
  }
  return currentMax;
}

template<typename T>
T DynamicArray<T>::min() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  float currentMin = 1e+38;
  for (int i = 0; i <= size; ++i) {
    if (data[i] <= currentMin) {
      currentMin = data[i];
    }
  }
  return currentMin;
}

template<typename T>
void DynamicArray<T>::clear() {
  if (this->data) {
    delete[] this->data;
    this->data = nullptr;
  }
  size = -1;
  capacity = 8;
}

template<typename T>
void DynamicArray<T>::reinitialize() {
  clear();
  data = new T[capacity]();
}

template<typename T>
void DynamicArray<T>::printData() {
  if (isEmpty()) {
    return;
  }
  for (int i = 0; i <= size; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}


template<typename T>
void DynamicArray<T>::push_front(T x){
  if (size+1 >= capacity){
    std::int64_t newCapacity = capacity*2;
    T* tempArray = new T[newCapacity];
    tempArray[0] = x;
    for (int i=1; i<=capacity; ++i){
      tempArray[i] = data[i-1];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  else{
    T* tempArray = new T[capacity];
    for(int i=1; i<=size+1; ++i){
      tempArray[i] = data[i-1];
    }
    tempArray[0] = x;
    delete[] data;
    data = tempArray;
  }
  ++size;
}

template<typename T>
T DynamicArray<T>::front(){
  return data[0];
}

template<typename T>
T DynamicArray<T>::back(){
  return data[size];
}

template<typename T>
void DynamicArray<T>::insert(std::int64_t ind, T val){
  if (ind>size+1 || ind<0){
    throw std::invalid_argument("index out of range");
  }
  else if (size+1>=capacity){
    std::int64_t newCapacity = capacity*2;
    T* tempArray = new T[newCapacity];
    for(int i=0; i<size; ++i){
      if (i==ind){ tempArray[i] = val;}
      else if (i>ind){ 
        tempArray[i] = data[i-1];
      }
      else{ tempArray[i] = data[i];}
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  else{
    for (int i=size+1; i>ind; --i){
      data[i] = data[i-1];
    }
    data[ind] = val;
  }
  ++size;
}

template<typename T>
void DynamicArray<T>::remove(std::int64_t ind){
  if (ind>size || ind<0){
    throw std::invalid_argument("index out of range");
  }
  for (int i=ind; i<=size; ++i){
    data[i] = data[i+1];
  }
  --size;
}

template<typename T>
void DynamicArray<T>::erase_after(std::int64_t ind){
  if (ind>size || ind<0){
    throw std::invalid_argument("index out of range");
  }
  T* tempArray = new T[capacity];
  for (int i=0; i<=ind; ++i){
    tempArray[i] = data[i];
  }
  size = ind;
  delete[] data;
  data = tempArray;
}

template<typename T>
void DynamicArray<T>::increase_capacity(std::int64_t newCap){
  if (newCap<=capacity){
    throw std::invalid_argument("new capacity less than old capacity or matches");
  }  
  T* tempArray = new T[newCap];
  for (int i=0; i<=size; ++i){
    tempArray[i] = data[i];
  }
  delete[] data;
  data = tempArray;
  capacity = newCap;
}

template<typename T>
void DynamicArray<T>::decrease_capacity(std::int64_t newCap){
  if (newCap>capacity){
    throw std::invalid_argument("new capacity exceed old capacity");
  }
  T* tempArray = new T[newCap];
  if (size>newCap){
    size = newCap-1;
  }
  for (int i=0; i<=size; ++i){
    tempArray[i] = data[i];
  }
  delete[] data;
  data = tempArray;
  capacity = newCap;
}

template<typename T>
T DynamicArray<T>::operator[](std::int64_t idx) {
  if (isEmpty() || idx < 0 || idx > size) {
    throw std::invalid_argument("Out of range");
  }
  return data[idx];
}

template<typename T>
T DynamicArray<T>::operator()() {
  if (isEmpty()) {
    return 0;
  }
  T sum = 0;
  for (int i = 0; i <= size; ++i) {
    sum += data[i];
  }
  return sum;
}

template<typename T>
DynamicArray<T> DynamicArray<T>:: operator+(const DynamicArray<T>& other){
  DynamicArray<T> newArr;
  newArr.capacity = (this->size + other.len())*2;
  newArr.size = this->size + other.len();
  for (int i=0; i<=this->size; ++i){
    newArr.data[i] = this->data[i];
  }
  for (int i=0; i<=other.size; ++i){
    newArr.data[this->size+i+1] = other[i];
  }
  return newArr;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>:: operator=(std::initializer_list<T> other){
  delete[] this->data;
  size = other.size()-1;
  capacity = other.size()*2;
  this->data = new T[capacity];

  int i=0;
  for(const T& el:other){
    this->data[i++] = el;
  }
  return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>:: operator=(const DynamicArray& other){
  this->capacity = other.capacity;
  this->size = other.size;
  T* newData = new T[this->capacity];
  for (int i=0; i<=this->size; ++i){
    newData[i] = other.data[i];
  }
  delete[] this->data;
  this->data = newData;
  return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>:: operator+=(std::initializer_list<T> other){
  for (const T& el : other) {
        push_back(el);
    }
    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>:: operator+=(DynamicArray& other){
  for (int i = 0; i < other.len(); ++i) {
        push_back(other.data[i]);
    }
    return *this;
} 

#endif