#ifndef STACK_H
#define STACK_H

#include "DynamicArray.h"
#include <cstdint>
#include <iostream>


template<typename T>
class Stack{
private:
    DynamicArray<T> stack;

public:
    Stack();
    Stack(std::int64_t capacity);
    Stack(std::initializer_list<T> stack);
    ~Stack()=default;

    void push(T x);
    T top();
    T pop(); 
    bool isEmpty();
    void printData();
    int size();
    Stack operator+(Stack<T>& other);
    Stack& operator=(const Stack<T>& other); 
    Stack& operator+=(Stack<T>& other);
    T operator[](std::int64_t ind);   
};

template<typename T>
Stack<T>::Stack():stack(){}

template<typename T>
Stack<T>::Stack(std::int64_t capacity):stack(capacity){}

template<typename T>
Stack<T>::Stack(std::initializer_list<T> stack){
  for (const T& el : stack) {
      this->stack.push_back(el);
    }
}

// template<typename T>
// Stack<T>::Stack(std::int64_t capacity):stack(stack& other){}

template<typename T>
void Stack<T>::push(T x){
    if (stack.len()>=stack.limit()){
        throw std::overflow_error("stack overflow");
    }
    stack.push_back(x);
}

template<typename T>
T Stack<T>::top(){
    if (isEmpty()){
        throw std::underflow_error("stack is empty");
    }
    return stack.back();
}

template<typename T>
T Stack<T>::pop(){
    if (isEmpty()){
        throw std::underflow_error("stack underflow");
    }
    T el = stack.back();
    stack.remove(stack.len()-1);
    return el;  
}

template<typename T>
bool Stack<T>::isEmpty(){
    return stack.isEmpty();
}

template<typename T>
void Stack<T>::printData(){
    stack.printData();
}

template<typename T>
int Stack<T>::size(){
    return stack.len();
}

template<typename T>
Stack<T> Stack<T>::operator+(Stack<T>& other){
    Stack<T> tempStack;
    for (int i=0; i<stack.len(); ++i){
        tempStack.push(this->stack[i]);
    }
    for (int i=0; i<other.size(); ++i){
        tempStack.push(other.stack[i]);
    }
    return tempStack;   
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other){
    this->stack = other.stack;    
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator+=(Stack<T>& other){
    for (int i=0; i<other.size(); ++i){
        push(other.stack[i]);
    }
    return *this;   
}

template<typename T>
T Stack<T>::operator[](std::int64_t ind){
    if (isEmpty() || ind<0 || ind> size()){
        throw std::invalid_argument("Out of range");
    }
    return this->stack[ind];
}

#endif