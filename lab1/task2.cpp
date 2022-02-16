#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#define mp make_pair

using namespace std;


int main()
{
    vector<string> stopWords = { "the", "on", "of", "in", "a", "an" };


    ifstream fin("task1.txt");


    vector<pair<string, vector<int>>> occurencies(1000000, mp("", vector<int>(101, false)));
    int curSize = 0;
    int curLine = 0;
    string s, line;
    char c;



readLine:
    if (!fin.eof()) {
        getline(fin, line);
        curLine++;
        stringstream ss(line);
    readLabel:
        if (ss >> s) {
            int i = 0;
            bool found = false;
        findLabel:
            if (i < curSize) {
                if (s == occurencies[i].first) {
                    found = true;
                    int j = 0;
                occurenciesLoop:
                    if (occurencies[i].second[j] == 0) {
                        occurencies[i].second[j] = curLine / 45 + 1;
                        j = 100;
                    }
                    j++;
                    if (j <= 100) {
                        goto occurenciesLoop;
                    }




                    i = curSize; //to break the loop
                }
                i++;
                goto findLabel;
            }

            if (!found) {
                occurencies[curSize].first = s;
                occurencies[curSize].second[0] = curLine / 45 + 1;
                curSize++;
            }
            goto readLabel;
        }
        goto readLine;
    }


    int j = 0;
    int i = 0;
outerLoop:
    if (i < curSize - 1) {
        j = 0;
    innerLoop:
        if (j < curSize - i - 1) {
            if (occurencies[j].first > occurencies[j + 1].first) {
                pair<string, vector<int>> temp = occurencies[j];
                occurencies[j] = occurencies[j + 1];
                occurencies[j + 1] = temp;
            }

            j++;
            goto innerLoop;
        }
        i++;
        goto outerLoop;
    }


    int n = curSize;
    i = 0;
printLabel:
    if (i < n) {
        if (occurencies[i].second[100] == 0) {
            cout << occurencies[i].first << '\n';
            int j = 0;
        printPagesLabel:
            if (occurencies[i].second[j] != 0) {
                cout << occurencies[i].second[j] << ' ';
                j++;
                goto printPagesLabel;
            }
            cout << '\n';
        }
        i++;

        goto printLabel;
    }
    return 0;
}
