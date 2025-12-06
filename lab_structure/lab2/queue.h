#ifndef QUEUE_H
#define QUEUE_H

#include "stack.h"
#include <cstdint>
#include <iostream>

template<typename T>
class Queue{
private:
    Stack<T> stack1;
    Stack<T> stack2;

public:
    Queue();
    Queue(std::int64_t capacity);
    Queue(std::initializer_list<T> queue);
    ~Queue()=default;

    void enqueue(T el);
    T dequeue();
    bool isEmpty();
    int size();
    void printData();
    Queue operator+(Queue<T>& other);
    Queue& operator=(const Queue<T>& other); 
    Queue& operator+=(Queue<T>& other); 
};

template<typename T>
Queue<T>::Queue():stack1(), stack2(){}

template<typename T>
Queue<T>::Queue(std::int64_t capacity):stack1(capacity), stack2(capacity){}

template<typename T>
Queue<T>::Queue(std::initializer_list<T> stack){
  for (const T& el : stack) {
      this->stack1.push(el);
    }
}

template<typename T>
void Queue<T>::enqueue(T el){
    stack1.push(el);
}

template<typename T>
T Queue<T>::dequeue(){
    if (stack2.isEmpty()){
        int s = stack1.size();
        for(int i=0; i<s; ++i){
            T x = stack1.pop();
            stack2.push(x);
        }
    }
    std::cout << std::endl;
    return stack2.pop();
}

template<typename T>
bool Queue<T>::isEmpty(){
    return (stack1.isEmpty() && stack2.isEmpty());
}

template<typename T>
int Queue<T>::size(){
    return stack1.size()+stack2.size();
}

template<typename T>
void Queue<T>::printData(){
    std::cout << "stack2: ";
    stack2.printData();
    std::cout << "stack1: ";
    stack1.printData();
}

template<typename T>
Queue<T> Queue<T>::operator+(Queue<T>& other){
    Queue<T> tempQueue;
    for (int i=0; i<this->stack1.size(); ++i){
        tempQueue.enqueue(this->stack1[i]);
    }
    for (int i=0; i<other.size(); ++i){
        tempQueue.enqueue(other.stack1[i]);
    }
    return tempQueue;   
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other){
    this->stack1 = other.stack1;    
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator+=(Queue<T>& other){
    for (int i=0; i<other.size(); ++i){
        enqueue(other.stack1[i]);
    }
    return *this;   
}

#endif