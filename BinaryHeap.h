#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "Job.h"

// Dynamic array-based binary heap of Job objects.
// Uses JobCompare to maintain heap order.
// When the array is full, it automatically resizes to 2x capacity.
class BinaryHeap
{
public:
    // Constructor: you can change the default initial capacity if you want.
    explicit BinaryHeap(int initialCapacity = 16);

    // Copy constructor and assignment operator
    BinaryHeap(const BinaryHeap& other);
    BinaryHeap& operator=(const BinaryHeap& other);

    // Destructor
    ~BinaryHeap();

    bool empty() const;
    int size() const;

    const Job& top() const;

    // Insert a new job into the heap.
    void push(const Job& value);

    // Remove the top job from the heap.
    void pop();

private:
    Job* data;       // dynamic array
    int heapSize;    // number of elements currently in the heap
    int capacity;    // current capacity of the array
    JobCompare comp; // comparison functor

    int parent(int i) const { return i / 2; }
    int left(int i) const { return 2 * i ; }
    int right(int i) const { return 2 * i + 1; }

    // Restore heap property upward from index idx.
    void heapifyUp(int idx);

    // Restore heap property downward from index idx.
    void heapifyDown(int idx);

    // Resize internal array to newCapacity, preserving existing elements.
    void resize(int newCapacity);
};

#endif // BINARY_HEAP_H