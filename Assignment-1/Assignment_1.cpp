#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 15;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

//Read data from a file
void readFile(const string& fileName, Student s[], int& n) {
    ifstream fin(fileName);
    if (!fin) {
        cerr << "File doesn't exist." << endl;
        return;
    }
    n = 0;
    while (fin >> s[n].rollNo >> s[n].name >> s[n].sgpa && n < MAX) {
        n++;
    }
    fin.close();
}

//Insertion sort
void insertionSortRoll(Student s[], int n) {
    for (int i = 1; i < n; i++) {
        Student temp = s[i];
        int j = i - 1;
        while (j >= 0 && s[j].rollNo > temp.rollNo) {
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = temp;
    }
}

//Shell sort
void shellSortName(Student s[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Student temp = s[i];
            int j;
            for (j = i; j >= gap && s[j - gap].name > temp.name; j -= gap) {
                s[j] = s[j - gap];
            }
            s[j] = temp;
        }
    }
}

int getMaxSGPA(Student s[], int n) {
    int max = (int)(s[0].sgpa * 100);
    for (int i = 1; i < n; i++) {
        if ((int)(s[i].sgpa * 100) > max)
            max = (int)(s[i].sgpa * 100);
    }
    return max;
}

//Counting sort
void countingSortSGPA(Student s[], int n, int exp) {
    Student output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[((int)(s[i].sgpa * 100) / exp) % 10]++;

    for (int i = 8; i >= 0; i--)
        count[i] += count[i + 1];

    for (int i = n - 1; i >= 0; i--) {
        int index = ((int)(s[i].sgpa * 100) / exp) % 10;
        output[count[index] - 1] = s[i];
        count[index]--;
    }

    for (int i = 0; i < n; i++)
        s[i] = output[i];
}

//Radix sort
void radixSortSGPA(Student s[], int n) {
    int max = getMaxSGPA(s, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortSGPA(s, n, exp);
}

//Write sorted data to a file
void writeSortedData(const string& fileName, Student original[], int n) {
    ofstream fout(fileName);
    if (!fout) {
        cerr << "Not able to write to file: " << fileName << endl;
        return;
    }

    Student rollSorted[MAX];
    for (int i = 0; i < n; i++) 
        rollSorted[i] = original[i];
    insertionSortRoll(rollSorted, n);

    fout << "\nSorted by Roll No :\n";
    fout << "Roll No\tName\t\tSGPA\n";
    for (int i = 0; i < n; i++)
        fout << rollSorted[i].rollNo << "\t" << rollSorted[i].name << "\t\t" << rollSorted[i].sgpa << "\n";

    Student nameSorted[MAX];
    for (int i = 0; i < n; i++) 
        nameSorted[i] = original[i];
    shellSortName(nameSorted, n);

    fout << "\nSorted by Name :\n";
    fout << "Roll No\tName\t\tSGPA\n";
    for (int i = 0; i < n; i++)
        fout << nameSorted[i].rollNo << "\t" << nameSorted[i].name << "\t\t" << nameSorted[i].sgpa << "\n";

    Student sgpaSorted[MAX];
    for (int i = 0; i < n; i++) 
        sgpaSorted[i] = original[i];
    radixSortSGPA(sgpaSorted, n);

    fout << "\nTop 10 Students by SGPA :\n";
    fout << "Roll No\tName\t\tSGPA\n";
    int top = (n < 10) ? n : 10;
    for (int i = 0; i < top; i++)
        fout << sgpaSorted[i].rollNo << "\t" << sgpaSorted[i].name << "\t\t" << sgpaSorted[i].sgpa << "\n";

    fout.close();
}

int main() {
    Student s[MAX];
    int n;
    string inputFile = "detail.txt";
    string outputFile = "output.txt";

    readFile(inputFile, s, n);

    writeSortedData(outputFile, s, n);

    return 0;
}

