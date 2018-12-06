#include <iostream>
#include <string>

using namespace std;

int main() {
    int sum = 0;
    for (string line; getline(cin, line);) {
        sum += stoi(line);
    }
    cout << to_string(sum) << endl;
}