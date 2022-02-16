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

    vector<pair<string, int>> dic(1000000);
    int curSize = 0;
    string s;
    char c;

readLabel:
    fin >> s;
    if (s[0] >= 65 && s[0] <= 90) {
        s[0] += 32;
    }

    int i = 0;
    bool found = false;
findStopWord:
    if (i < stopWords.size()) {
        if (s == stopWords[i]) {
            goto readLabel;
        }
        i++;
        goto findStopWord;
    }



    i = 0;
    found = false;
findLabel:
    if (i < curSize) {
        if (s == dic[i].first) {
            found = true;
            dic[i].second++;
            i = curSize; //to break the loop
        }
        i++;
        goto findLabel;
    }

    if (!found) {
        dic[curSize++] = mp(s, 1);
    }
    if (!fin.eof()) {
        goto readLabel;
    }


    int j = 0;

    i = 0;
outerLoop:
    if (i < curSize - 1) {
        j = 0;
    innerLoop:
        if (j < curSize - i - 1) {
            if (dic[j].second < dic[j + 1].second) {
                pair<string, int> temp = dic[j];
                dic[j] = dic[j + 1];
                dic[j + 1] = temp;
            }

            j++;
            goto innerLoop;
        }
        i++;
        goto outerLoop;
    }


    int n;
    cin >> n;

    if (n > curSize) {
        n = curSize;
    }

    i = 0;
printLabel:
    if (i < n) {
        cout << dic[i].first << " : " << dic[i].second << '\n';
        i++;
        goto printLabel;
    }
    return 0;
}
