#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 20;

struct Employee {
    int EMP_ID;
    string name;
    float salary;
};

//Read data from a file
void readFile(const string& fileName, Employee e[], int& n) {
    ifstream fin(fileName);
    if (!fin) {
        cerr << "File doesn't exist." << endl;
        return;
    }
    n = 0;
    while (fin >> e[n].EMP_ID >> e[n].name >> e[n].salary && n < MAX) {
        n++;
    }
    fin.close();
}

//Quick Sort

int partition(Employee arr[], int low, int high) {
    int pivot = arr[high].EMP_ID;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].EMP_ID <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Employee arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void EMP_ID_sort(Employee e[], int n) {
    quickSort(e, 0, n - 1);
}

void merge(Employee arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Employee* L = new Employee[n1];
    Employee* R = new Employee[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].name <= R[j].name) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// Recursive merge sort
void mergeSort(Employee arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


void Merge_sort_name(Employee e[], int n) {
    mergeSort(e, 0, n - 1);
}

//Write sorted data to a file
void writeSortedData(const string& fileName, Employee original[], int n) {
    ofstream fout(fileName);
    if (!fout) {
        cerr << "Not able to write to file: " << fileName << endl;
        return;
    }

    Employee rollSorted[MAX];
    for (int i = 0; i < n; i++) 
        rollSorted[i] = original[i];
    EMP_ID_sort(rollSorted, n);

    fout << "\nSorted by EMP ID :\n";
    fout << "EMP_ID\tName\t\tSalary\n";
    for (int i = 0; i < n; i++)
        fout << rollSorted[i].EMP_ID << "\t" << rollSorted[i].name << "\t\t" << rollSorted[i].salary << "\n";

    Employee nameSorted[MAX];
    for (int i = 0; i < n; i++) 
        nameSorted[i] = original[i];
    Merge_sort_name(nameSorted, n);

    fout << "\nSorted by Name :\n";
    fout << "EMP_ID\tName\t\tSalary\n";
    for (int i = 0; i < n; i++)
        fout << nameSorted[i].EMP_ID << "\t" << nameSorted[i].name << "\t\t" << nameSorted[i].salary << "\n";

    fout.close();
}

int main() {
    Employee e[MAX];
    int n;
    string inputFile = "details.txt";
    string outputFile = "output.txt";

    readFile(inputFile, e, n);

    writeSortedData(outputFile, e, n);

    return 0;
}
