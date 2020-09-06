#include <memory>
#include <stdio.h>
#include <iostream>
#include <mutex>
#include <condition_variable>

template <class T> class Queue{
    private:
        T* data = nullptr;
        int front = -1;
        int rear = -1;
        mutex mut;
        condition_variable cond;
    public:
    int count = 0;
    int size;

    Queue(){}

    Queue(size_t max_elems){
        mutex(mut);
        condition_variable(cond);
        data = (T*)malloc(max_elems*sizeof(T));
        size = max_elems;

    }

    ~Queue(){
        free(data);
    }

    Queue(const Queue<T>& other){
        free(data);
        data = other.data;
        front = other.front;
        rear = other.rear;
    }

    void ld(const Queue<T>&other){
        free(data);
        data = other.data;
        front = other.front;
        rear = other.rear;
    }

    bool isfull(){
        bool out;
        lock_guard<mutex> lock(mut);
        out = (front==0&&rear==size-1) || (front==rear+1);
        cond.notify_one();
        return out;

    }        
    bool empty(){
        bool out;
        lock_guard<mutex> lock(mut);
        out = (front==-1 || front==rear );
        cond.notify_one();
        return out;
    }

    void enqueue(T elem){
        lock_guard<mutex> lock(mut);
        count++;
        if(front==-1){
            front++;
        }
        rear++;
        if(rear==size-1){
            if(isfull()){
                std::cout << "QueueOverflow error." << std::endl;
                exit(1);
            }
            rear=0;
        }
        data[rear]=elem;
        cond.notify_one();

    }

    void dequeue(T* dest){
        
        lock_guard<mutex> lock(mut);
        count--;
        if(front == -1){
            std::cout << "QueueUnderflow error." << std::endl;
            exit(1);
        }
        *dest = data[front];
        front++;
        if(front==size-1){
            
            front=0;
        }
        cond.notify_one();

    }

    T dequeue(){
        lock_guard<mutex> lock(mut);
        count--;

        if(front == -1){
            std::cout << "QueueUnderflow error." << std::endl;
            exit(1);
        }
        T out = data[front];
        front++;
        if(front==size-1){
            front=0;
        }


        cond.notify_one();

        return out;

    }



};