#include "BinaryHeap.h"
#include <stdexcept>

BinaryHeap::BinaryHeap(int initialCapacity)
    : data(nullptr),
      heapSize(0),
      capacity(0),
      comp()
{
    // Ensure capacity is at least 1
    if (initialCapacity < 1){
        initialCapacity = 1;
    }
    capacity = initialCapacity;
    data = new Job[capacity + 1];
}

BinaryHeap::BinaryHeap(const BinaryHeap& other): data(nullptr),heapSize(other.heapSize),capacity(other.capacity),comp(other.comp){
    data = new Job[capacity + 1];
    for (int i = 1; i <= heapSize; i++){
        data[i] = other.data[i];
    }
}

BinaryHeap& BinaryHeap::operator=(const BinaryHeap& other){
    if (this == &other){
        return* this;
    }

    delete[] data;

    capacity = other.capacity;
    heapSize = other.heapSize;
    comp = other.comp;

    data = new Job[capacity + 1];
    for (int i = 1; i <= heapSize; i++){
        data[i] = other.data[i];
    }

    return *this;
}

BinaryHeap::~BinaryHeap()
{
    delete[] data;
    data = nullptr;
    heapSize = 0;
    capacity = 0;
}

bool BinaryHeap::empty() const
{
    if(heapSize == 0){
        return true;
    }
    return false;
}

int BinaryHeap::size() const
{
    return heapSize;
}

const Job& BinaryHeap::top() const
{   
    if(heapSize == 0){
        throw std::runtime_error("Heap is empty");
    }
    return data[1];
}

void BinaryHeap::push(const Job& value)
{   
    if (heapSize == capacity)
    {
        resize(capacity * 2);
    }
    data[++heapSize] = value;
    heapifyUp(heapSize);
}

void BinaryHeap::pop()
{   
    if(heapSize == 0){
        throw std::runtime_error("Heap is empty");
    }

    data[1] = data[heapSize--];
    

    if(heapSize > 0){
        heapifyDown(1);
    }

}

void BinaryHeap::heapifyUp(int idx){

    while(idx > 1){
        int p = parent(idx);
        if(comp(data[p],data[idx])){
            Job temp = data[p];
            data[p] = data[idx];
            data[idx] = temp;
            idx = p;
        }else{
            break;
        }
    }
}

void BinaryHeap::heapifyDown(int idx)
{
    while(1){
        int l = left(idx);
        int r = right(idx);
        int optimal = idx;

        if(l <= heapSize && r > heapSize){
            optimal = l;
        }else if(r <= heapSize && l > heapSize){
            optimal = r;
        }else if(r > heapSize && l > heapSize){
            break;
        }else{
            if(comp(data[l],data[r])){
                optimal = r;
            }else{
                optimal = l;
            }
        }
        if(comp(data[idx],data[optimal])){
            Job temp = data[optimal];
            data[optimal] = data[idx];
            data[idx] = temp;
            idx = optimal;
        }else{
            break;
        }
    }
}

void BinaryHeap::resize(int newCapacity)
{      

    if(newCapacity < 1){
        newCapacity = 1;
    }
    Job* newData = new Job[newCapacity + 1];
    for(int i = 1;i<= heapSize;i++){
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}