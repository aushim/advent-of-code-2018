#include <iostream>
#include <string>
#include <vector>
#include <cstring>
 
using namespace std;

vector<string> split(string& str)
{
    vector<string> results;
    char * pch;
    string separators = " #@,:x";
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

int main() {
    vector<vector<int> > fabric(1000, vector<int>(1000));

    vector<string> claims;
    for (string line; getline(cin, line);) {
        claims.push_back(line);
    }

    for (string& claim : claims) {
        vector<string> parts = split(claim);
        int begin_x = stoi(parts[1]);
        int begin_y = stoi(parts[2]);
        int end_x = begin_x + stoi(parts[3]);
        int end_y = begin_y + stoi(parts[4]);
        for (int i = begin_x; i < end_x; i++) {
            for (int j = begin_y; j < end_y; j++) {
                fabric[i][j] = fabric[i][j] == 0 ? 1 : -1;
            }
        }
    }

    int area = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (fabric[i][j] == -1) {
                area++;
            }
        }
    }

    cout << to_string(area) << endl;

    return 0;
}