#include <iostream>
#include <string>
#include <vector>
#include <cstring>
 
using namespace std;

vector<string> split(string& str, const string& separators) {
    vector<string> results;
    char * pch;
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    pch = strtok(cstr, separators.c_str());
    while (pch != NULL) {
        results.push_back(pch);
        pch = strtok (NULL, separators.c_str());
    }
    delete [] cstr;
    return results;
}

vector<int> numbers(10000, -1);

pair<int, int> get_node_sum(int begin) {
    if (numbers[begin] == -1) {
        return make_pair(0, begin);
    }
    int nodes = numbers[begin];
    int data = numbers[begin + 1];
    int sum = 0;
    int new_begin = begin + 2;
    while (nodes > 0) {
        pair<int, int> result = get_node_sum(new_begin);
        sum += result.first;
        new_begin = result.second;
        nodes--;
    }
    for (int i = new_begin; i < new_begin + data; i++) {
        sum += numbers[i];
    }
    new_begin += data;
    return make_pair(sum, new_begin);
}

int main() {
    string line;
    getline(cin, line);
    vector<string> parts = split(line, " ");
    for (int i = 0; i < parts.size(); i++) {
        numbers[i] = stoi(parts[i]);
    }
    cout << to_string(get_node_sum(0).first) << endl;
    return 0;
}