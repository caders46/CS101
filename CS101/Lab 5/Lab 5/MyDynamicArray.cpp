#include <iostream>

using namespace std;

class MyDynamicArray {
private:
    int size, capacity, error;
    int* a;
public:
    MyDynamicArray() {
        capacity = 2;
        size = 0;
        error = 0;
        a = new int[capacity];
    }
    MyDynamicArray(int s) {
        /* Your code goes here */
        capacity = s;
        size = s;
        error = 0;
        a = new int[capacity];
    }
    int& operator[](int i) {
        /* Your code goes here */
        if (i >= size) {
            cout << "Out of bounds reference: " << i << endl;
            int& r = error;
            return r;
        }
        else {
            return a[i];
        }

    }
    void add(int v) {
        /* Your code goes here */
        a[size] = v;
        size++;
        if (size == capacity) {
            capacity *= 2;
            cout << "Doubling to: " << capacity << endl;
        }
    }
    void del() {
        size--;
        if (size <= capacity / 4) {
            capacity /= 2;
            cout << "Reducing to: " << capacity << endl;
        }
        /* Your code goes here */
    }
    int length() {
        return size;
    }
    void clear() {
        size = 0;
        capacity = 2;
        /* Your code goes here */
    }
};
