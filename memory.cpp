#include<iostream>
using namespace std;

struct Block {
    int ID; //ID process 0 if free
    int size; //size of memory block
    bool free; //is block free?
    Block *prev;
    Block *next;
    
    Block(int s, bool f = true, int i = 0) {
        size = s;
        free = f;
        ID = i;
        prev = next = NULL;
    }
};

class Memory {
    Block *head;
public:
    Memory(int totalSize) {
        head = new Block(totalSize, true, 0); //one big free block
    }
    
    void allocate(int PId, int size) {
        Block *curr = head;
        while(curr) {
            if(curr->free && curr->size >= size) {
                if(curr->size > size) {
                    Block *nBlock = new Block(curr->size - size);
                    nBlock->free = true;
                    nBlock->prev = curr;
                    nBlock->next = curr->next;
                    
                    if(curr->next)
                        curr->next->prev = nBlock;
                    curr->next = nBlock;
                    curr->size = size;
                }
                
                curr->free = false;
                curr->ID = PId;
                cout<<"Allocated "<<size<<" units to process "<<PId<<"\n";
                return;
            }
            curr = curr->next;
        }
        cout<<"Allocation failed: Not enough memory\n";
    }
    
    void deallocate(int PId) {
        Block *curr = head;
        while(curr) {
            if(!curr->free && curr->ID == PId) {
                curr->free = true;
                curr->ID = 0;
                cout<<"Deallocated process "<<PId<<"\n";
                return;
            }
            curr = curr->next;
        }
        cout<<"Process "<<PId<<" not found\n";
    }
    
    void garbageCollect() {
        cout<<"\nPerforming garbage collection..\n";
        //Merge
        Block *curr = head;
        while(curr && curr->next) {
            if(curr->free && curr->next->free) {
                Block *temp = curr->next;
                curr->size += temp->size;
                curr->next = temp->next;
                if(temp->next)
                    temp->next->prev = curr;
                delete temp;
            }
            else {
                curr = curr->next;
            }
        }
        
        //shift allocated free blocks to start
        Block *fBlock = head;
        curr = head;
        while(curr) {
            if(!curr->free && fBlock->free) {
                swap(curr->ID, fBlock->ID);
                swap(curr->size, fBlock->size);
                swap(curr->free, fBlock->free);
            }
            if(!fBlock->free)
                fBlock = fBlock->next;
            curr = curr->next;
        }
        
        //Merge free blocks
        curr = head;
        while(curr && curr->next) {
            if(curr->free && curr->next->free) {
                Block *temp = curr->next;
                curr->size += temp->size;
                curr->next = temp->next;
                
                if(temp->next)
                    temp->next->prev = curr;
                delete temp;
            }
            else {
                curr = curr->next;
            }
        }
        cout<<"Garbage collection complete!\n";
    }
    
    void display() {
        cout<<"\n--Memory layout--\n";
        cout<<"Block#\tPID\tSize\tStatus\n";
        Block *curr = head;
        int index = 1;
        while(curr) {
            cout<<index++<<"\t"<<(curr->ID ? curr->ID : 0)<<"\t"<<curr->size<<"\t"<<(curr->free ? "Free" : "Used")<<"\n";
            curr = curr->next;
        }
    }
};

int main() {
    int TSize;
    cout<<"Enter total memory size: ";
    cin>>TSize;
    
    Memory m(TSize);
    int choice;
    do {
        cout<<"\nMemory Manager: \n";
        cout<<"1. Allocate Memory\n";
        cout<<"2. Deallocate Memory\n";
        cout<<"3. Display Memory\n";
        cout<<"4. Garbage Collect\n";
        cout<<"5. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
        
        if(choice == 1) {
            int PId, size;
            cout<<"Enter process ID: ";
            cin>>PId;
            cout<<"Enter size to allocate: ";
            cin>>size;
            m.allocate(PId, size);
        }
        
        else if(choice == 2) {
            int PId;
            cout<<"Enter process ID to deallocate: ";
            cin>>PId;
            m.deallocate(PId);
        }
        
        else if(choice == 3) {
            m.display();
        }
        
        else if(choice == 4) {
            m.garbageCollect();
        }
        
        else if(choice != 5) {
            cout<<"Invalid choice!\n";
        }
    }
    while(choice != 5);
    cout<<"Exiting..\n";
    return 0;
}
              
            
        
        
        
            
          
