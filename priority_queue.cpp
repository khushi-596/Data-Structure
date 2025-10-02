//Priority Queue using heap
#include<iostream>
#include<climits>
#include<cstdlib>
using namespace std;

struct Node {
    int id;
    int time;
};

class Heap {
    Node heap[100];
    int size;
    
    void heapify(int i) {
        int smallest = i;
        int left = 2*i, right = 2*i + 1;
        if(left <= size && heap[left].time < heap[smallest].time)
            smallest = left;
        if(right <= size && heap[right].time < heap[smallest].time)
            smallest = right;
        if(smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
public:
    Heap() {
        size = 0;
    }
    
    void insert(Node p) {
        heap[++size] = p;
        int i = size;
        while(i > 1 && heap[i].time < heap[i/2].time) {
            swap(heap[i], heap[i/2]);
            i /= 2;
        }
    }
    
    Node remove() {
        if(size == 0)
            return {-1, INT_MAX};
        Node min = heap[1];
        heap[1] = heap[size--];
        heapify(1);
        return min;
    }
    
    bool empty() {
        return size == 0;
    }
};

int main() {
    Heap h;
    for(int i = 1; i <= 5; i++) {
        int b = rand() % 20 + 1;
        h.insert({i, b});
    }
    while(!h.empty()) {
        Node curr = h.remove();
        cout<<"Process "<<curr.id<<" executed with time "<<curr.time<<endl;
    }
    return 0;
}
    
