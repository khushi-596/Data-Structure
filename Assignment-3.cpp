//Task manager
#include<iostream>
#include<string>
using namespace std;

struct Task {
    string name;
    int priority;
    float est;
    int serial;
    Task* next;
    static int serialCounter;
};

int Task::serialCounter = 1;

class TaskManager {
    Task* head, * tail;

public:
    TaskManager() {
        head = tail = NULL;
        Task::serialCounter = 1;
    }

    // Display tasks from priority 5 to 1
    void display() {
    if (!head) {
        cout << "Empty list" << endl;
        return;
    }

    cout << "S.No     Task                Priority   Estimated Time" << endl;
    cout << "------------------------------------------------------" << endl;

    for (int p = 5; p >= 1; --p) {
        Task* tp = head;
        while (tp) {
            if (tp->priority == p) {
                cout << tp->serial;
                int len = to_string(tp->serial).length();
                for (int i = len; i < 8; ++i) cout << ' ';

                cout << tp->name;
                len = tp->name.length();
                for (int i = len; i < 20; ++i) cout << ' ';

                cout << tp->priority;
                len = to_string(tp->priority).length();
                for (int i = len; i < 10; ++i) cout << ' ';

                cout << tp->est;
                len = to_string(tp->est).length();
                for (int i = len; i < 15; ++i) cout << ' ';

                cout << endl;
            }
            tp = tp->next;
        }
    }

    cout << endl;
}


    // Add task
    void AddTask(string name, int priority, float est) {
        Task* newTask = new Task{name, priority, est, Task::serialCounter++, NULL};

        if (!head) {
            head = tail = newTask;
        }
        else if (priority == 5) {
            newTask->next = head;
            head = newTask;
        }
        else if (priority == 1) {
            tail->next = newTask;
            tail = newTask;
        }
        else {
            Task* ptr = head;
            while (ptr->next && ptr->next->priority >= priority) {
                ptr = ptr->next;
            }

            newTask->next = ptr->next;
            ptr->next = newTask;

            if (newTask->next == NULL) {
                tail = newTask;
            }
        }
    }
    
    // Remove priority 5 task with smallest estimated time
    void removePriority() {
        Task* curr = head;
        Task* prev = nullptr;
        Task* minPrev = nullptr;
        Task* minNode = nullptr;

        while (curr) {
            if (curr->priority == 5) {
                if (!minNode || curr->est < minNode->est) {
                    minNode = curr;
                    minPrev = prev;
                }
            }
            prev = curr;
            curr = curr->next;
        }

        if (minNode) {
            if (minNode == head) {
                head = head->next;
                if (!head) tail = nullptr;
            } else {
                minPrev->next = minNode->next;
                if (minNode == tail)
                    tail = minPrev;
            }

            cout << "Deleted task with priority 5 and minimum time: " << minNode->name << endl;
            delete minNode;
        } else {
            cout << "No task with priority 5 found." << endl;
        }
    }


    // Remove task by name
    void removeTask(string name) {
        if (!head) {
            cout << "Task list is empty." << endl;
            return;
        }

        Task* curr = head;
        Task* prev = NULL;

        if (head->name == name) {
            head = head->next;
            delete curr;
            if (!head) tail = NULL;
            cout << "Task removed." << endl;
            return;
        }

        while (curr && curr->name != name) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) {
            cout << "Task not found." << endl;
            return;
        }

        prev->next = curr->next;
        if (curr == tail) {
            tail = prev;
        }
        delete curr;
        cout << "Task removed successfully." << endl;
    }

    // Display count of tasks by priority
    void DisplayPriCount() {
        int count[6] = { 0 };
        Task* tp = head;
        while (tp) {
            if (tp->priority >= 1 && tp->priority <= 5)
                count[tp->priority]++;
            tp = tp->next;
        }
        cout << "Count of tasks by priority:\n";
        for (int i = 1; i <= 5; i++) {
            cout << "Priority " << i << ": " << count[i] << " tasks." << endl;
        }
    }

    // Display total task and time
    void DisplayToTask() {
        int totalTask = 0;
        float totalTime = 0;
        Task* tp = head;
        while (tp) {
            totalTask++;
            totalTime += tp->est;
            tp = tp->next;
        }
        cout << "Total tasks: " << totalTask << endl;
        cout << "Total estimated time: " << totalTime << endl;
    }

    // Search task
    void search(string name) {
        Task* curr = head;
        while (curr && curr->name != name)
            curr = curr->next;
        if (!curr) {
            cout << "Task not found." << endl;
            return;
        }
        cout << "Task found: " << curr->name << ", Priority: " << curr->priority << ", Estimated Time: " << curr->est << endl;
    }

    // Update task
    void updateTask(string name) {
        Task* curr = head;
        while (curr && curr->name != name)
            curr = curr->next;

        if (!curr) {
            cout << "Task not found." << endl;
            return;
        }

        cout << "Enter new name (or press Enter to keep \"" << curr->name << "\"): ";
        cin.ignore();
        string newName;
        getline(cin, newName);
        if (!newName.empty())
            curr->name = newName;

        cout << "Enter new priority (1-5) or -1 to keep current (" << curr->priority << "): ";
        int newPriority;
        cin >> newPriority;
        if (newPriority >= 1 && newPriority <= 5)
            curr->priority = newPriority;

        cout << "Enter new estimated time (or -1 to keep current: " << curr->est << "): ";
        float newEst;
        cin >> newEst;
        if (newEst >= 0)
            curr->est = newEst;

        cout << "Task updated." << endl;
    }
};

int main() {
    TaskManager m;
    int choice;

    while (true) {
        cout << "\n-- Task Manager --\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task by Name\n";
        cout << "3. Display Tasks\n";
        cout << "4. Display Count by Priority\n";
        cout << "5. Display Total Tasks and Time\n";
        cout << "6. Update Task\n";
        cout << "7. Remove task with minimum time\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int priority;
            float est;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter priority (1 to 5): ";
            cin >> priority;
            cout << "Enter estimated time: ";
            cin >> est;
            m.AddTask(name, priority, est);
        }

        else if (choice == 2) {
            string name;
            cout << "Enter task name to remove: ";
            cin.ignore();
            getline(cin, name);
            m.removeTask(name);
        }

        else if (choice == 3) {
            m.display();
        }

        else if (choice == 4) {
            m.DisplayPriCount();
        }

        else if (choice == 5) {
            m.DisplayToTask();
        }

        else if (choice == 6) {
            string name;
            cout << "Enter task name to update: ";
            cin.ignore();
            getline(cin, name);
            m.updateTask(name);
        }

        else if (choice == 7) {
            m.removePriority();
        }
        
        else if (choice == 8) {
            cout << "Exiting..." << endl;
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}


