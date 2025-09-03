#include <iostream>
#include "stack.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <string>\n";
        return 1;
    }

    string Str = argv[1];
    int len = Str.length();

    stack<char> S(len);

    for (int i = 0; i < len; i++) {
        S.push(Str[i]);
    }

    for (int i = 0; i < len; i++) {
        if (Str[i] != S.pop()) {
            cout << "\nNot a palindrome\n";
            return 0;
        }
    }

    cout << "\nIt is a palindrome\n";
    return 0;
}

