#include <memory>
#include <stdio.h>
#include <iostream>
#include <mutex>



template <class T> class Queue{
    private:
        T* data = nullptr;
        int front = -1;
        int rear = -1;
        std::mutex mut;
    public:

    int size;
    int count;

    Queue(size_t max_elems){
        std::mutex(mut);
        data = new T[max_elems];
        size = max_elems;

    }

    ~Queue(){
        free(data);
    }

    Queue(const Queue& other) : Queue(other.size){
        free(other.data);
    }

    bool isfull(){

        return (front==0&&rear==size-1) || (front==rear+1);

    }
    bool empty(){

        return (front == -1);

    }

    void ld(const Queue& other){

        free(data);
        data = other.data;
        front = other.front;
        rear = other.rear;
        size = other.size;

    }

    void enqueue(T value){
        std::lock_guard<mutex> lock(mut);
        if(( front == 0 && rear == size-1 ) ||  (  rear==(front-1)%(size-1)  )){
            //queue full
            cout << "QUEUE FULL!!!!" << endl;
            exit(1);
        }
        else if (front == -1){
            front = rear = 0;
            data[rear]=value;
        }else if (rear == size-1 && front != 0){
            rear = 0;
            data[rear] = value;
        }else{
            rear++;
            data[rear] = value;
        }
        
        count ++;
    }



    bool dequeue(T* dest){



        std::lock_guard<mutex> lock(mut);

        if(front == -1){
            cout << "QUEUE EMPTY!!!" << endl;
            return false;
        }

        T out = data[front];
        if(front == rear){
            front = rear = -1;
        }
        else if (front == size-1){
            front = 0;
        }else{
            front++;
        }
        count --;
        *dest = out;
        return true;






        
    }


    void reset(){
        free(data);
        data = new T[size];
        front = -1;
        rear = -1;
        count = 0;


    }

};