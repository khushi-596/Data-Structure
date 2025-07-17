#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;

int insertion_Compare = 0;
int insertion_swap = 0;
int shell_compare = 0;
int shell_swap = 0;

vector<int> sizes = {100, 500, 1000, 5000, 10000, 15000, 20000, 25000};
int range = 1000;

void generate(const string& FileName, int n) {
    ofstream file(FileName);
    for (int i=0; i<n; i++) {
        file<<rand()%range + 1<<"\n";
    }
    file.close();
}


void insertion_sort(vector<int> &arr) {
    insertion_Compare = insertion_swap = 0;
    int n = arr.size();
    for(int i=1; i<n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0) {
            insertion_Compare++;
            if(arr[j] > key) {
                arr[j + 1] = arr[j];
                
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
        insertion_swap++;
    }
}

void shell_sort(vector<int> &arr) {
    shell_compare = shell_swap = 0;
    int n = arr.size();
    for(int gap=n/2; gap>0; gap=gap/2) {
        for(int i=gap; i<n; i++) {
            int key = arr[i];
            int j = i;
            while(j >= gap) {
                shell_compare++;
                if(arr[j - gap] > key) {
                    arr[j] = arr[j - gap];
                    shell_swap++;
                    j -= gap;
                }
                else {
                    break;
                }
            }
            arr[j] = key;
             
        }
    }
}


vector<int> read_file(string FileName) {
    vector<int> data;
    ifstream file(FileName);
    if(!file) {
        cerr<<"Error opening file";
        return data;
    }
    int no;
    while(file >> no) {
        data.push_back(no);
    }
    return data;
}

int main() {
    ofstream result("sort_results.txt");

    for (int i = 0; i < sizes.size(); ++i) {
    string FileName = "f" + to_string(i + 1) + ".txt";
    generate(FileName, sizes[i]);
    vector<int> data1 = read_file(FileName);
    vector<int> data2 = data1;

    insertion_sort(data1);
    shell_sort(data2);

    cout << "\nResults for " << FileName << ":\n";
    cout << "Insertion Sort:- Comparisons: " << insertion_Compare << ", Swaps: " << insertion_swap << "\n";
    cout << "Shell Sort:- Comparisons: " << shell_compare << ", Swaps: " << shell_swap << "\n";

    result << "Results for " << FileName << " (n = " << sizes[i] << ")\n";
    result << "Insertion Sort:- Comparisons: " << insertion_Compare << ", Swaps: " << insertion_swap << "\n";
    result << "Shell Sort:- Comparisons: " << shell_compare << ", Swaps: " << shell_swap << "\n\n";
    }

    result.close();

    return 0;
}