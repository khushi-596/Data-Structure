#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <cstdlib>

using namespace std;

struct Employee {
    int EmpId;
    string Name;
    string Dept;
};

int stringToInt(string s) {
    int num = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 10 + (s[i] - '0');
        }
    }
    return num;
}

int readFromFile(Employee eArr[], string filename) {
    ifstream fin(filename);
    string line;
    int count = 0;

    while (getline(fin, line)) {
        if (line == "")
            continue;
        string id = "", name = "", dept = "";
        int field = 0;
        for (int i = 0; i < line.size(); i++) {
            char ch = line[i];
            if (ch == ',')
                field++;
            else {
                if (field == 0)
                    id += ch;
                else if (field == 1)
                    name += ch;
                else
                    dept += ch;
            }
        }
        eArr[count].EmpId = stringToInt(id);
        eArr[count].Name = name;
        eArr[count].Dept = dept;
        count++;
    }
    fin.close();
    return count;
}

// Write comparisons to file
void writeToFile(string filename, string m) {
    ofstream fout(filename, ios::app);
    fout << m << endl;
    fout.close();
}

int hashFunction(int key, int size) {
    return key % size;
}

// Linear probing insert
void insertRecord(Employee hashT[], int size, Employee emp) {
    int index = hashFunction(emp.EmpId, size);
    while (hashT[index].EmpId != INT_MIN) {
        index = (index + 1) % size;
    }
    hashT[index] = emp;
}

// Hash search
int hashSearch(Employee hashT[], int size, int key, int &count) {
    int index = hashFunction(key, size);
    count = 0;
    while (hashT[index].EmpId != INT_MIN) {
        count++;
        if (hashT[index].EmpId == key)
            return index;
        index = (index + 1) % size;
    }
    return -1;
}

// Linear search
int linearSearch(Employee eArr[], int n, int key, int &count) {
    count = 0;
    for (int i = 0; i < n; i++) {
        count++;
        if (eArr[i].EmpId == key)
            return i;
    }
    return -1;
}

void display(Employee eArr[], int n) {
    cout << "\nEmployee records\n";
    for (int i = 0; i < n; i++) {
        cout << "EmpId: " << eArr[i].EmpId 
             << " | Name: " << eArr[i].Name 
             << " | Dept: " << eArr[i].Dept << endl;
    }
}

int main() {
    Employee eArr[50];
    Employee hashT[100];
    int n, size, choice, key, countHash, countLinear;

    n = readFromFile(eArr, "Employee_details.txt");
    size = n * 2;
    for (int i = 0; i < size; i++)
        hashT[i].EmpId = INT_MIN;

    for (int i = 0; i < n; i++)
        insertRecord(hashT, size, eArr[i]);

    do {
        cout << "\n---menu---\n";
        cout << "1. Display all employees\n";
        cout << "2. Search by ID using hash search\n";
        cout << "3. Search by ID using linear search\n";
        cout << "4. Compare both searches\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                display(eArr, n);
                break;

            case 2:
                cout << "Enter Employee ID to search: ";
                cin >> key;
                if (hashSearch(hashT, size, key, countHash) != -1)
                    cout << "Record found with " << countHash << " comparisons.\n";
                else
                    cout << "Record not found. Comparisons: " << countHash << endl;
                break;

            case 3:
                cout << "Enter Employee ID to search: ";
                cin >> key;
                if (linearSearch(eArr, n, key, countLinear) != -1)
                    cout << "Record found with " << countLinear << " comparisons.\n";
                else
                    cout << "Record not found. Comparisons: " << countLinear << endl;
                break;

            case 4:
                cout << "Enter Employee ID to compare: ";
                cin >> key;
                hashSearch(hashT, size, key, countHash);
                linearSearch(eArr, n, key, countLinear);
                cout << "Hash Search Comparisons: " << countHash << endl;
                cout << "Linear Search Comparisons: " << countLinear << endl;
                writeToFile("Output.txt", "Key " + to_string(key) + ": Hash=" + to_string(countHash) + " | Linear=" + to_string(countLinear));
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

