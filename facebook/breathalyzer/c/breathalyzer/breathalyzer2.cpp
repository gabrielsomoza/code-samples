#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <climits>
using namespace std;

#define DICTSIZE 178691

int checkwords(string a, string b, int k) {
    int n = a.size();
    int m = b.size();
    int longer = (m > n) ? m : n;
    if ((m == 0) || (n == 0)) {
        return longer;
    }
    if (k > longer) {
        k = longer;
    }
    int v1[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        v1[i][0] = i;
    }

    int iup = (n <= (m + k)) ? n : (m + k);
    int ullast = k + 1;
    int x;
    int y;
    int z;
    int ll = 0;
    int ul = 0;
    int cost;
    int first;
    int minv;

    for (int i = 0; i < iup; i++) {
        v1[0][i + 1] = i + 1;
        char ai = a[i];
        ll = (i <= k) ? 0 : (i - k);
        ul = ((i + k) >= m) ? m : (i + k + 1);
        for (int j = ll; j < ul; j++) {
            cost = (ai == b[j]) ? 0 : 1;
            x = ((j > ll) || (j == 0)) ? (v1[j][i + 1] + 1) : longer;
            y = ((j == (ul - 1)) && (ul > ullast)) ? longer : (v1[j + 1][i] + 1);
            z = v1[j][i] + cost;
            first = (x < y) ? x : y;
            v1[j + 1][i + 1] = (z < first) ? z : first;
        }
        ullast = ul;
        minv = v1[i + 1][ll];
        for (int t = ll + 1; t <= ul; t++) {
            if (v1[t][i + 1] < minv) {
                minv = v1[t][i + 1];
            }
        }
        if (minv >= k) {
            return k;
        }
    }
    /*
    printf("    ");
    for (int j = 0; j <= n; j++) {
      printf("  %c", a[j]);
    }
    cout << endl;
    for (int i = 0; i <= m; i++) {
      if (i > 0) {
        printf("%c", b[i-1]);
      } else {
        printf(" ");
      }
      for (int j = 0; j <= n; j++) {
        printf("%3d", v1[i][j]);
      }
      cout << endl;
    }
     */
    return v1[ul][iup];
}

string uppercase(string strToConvert) {
    for (unsigned int i = 0; i < strToConvert.length(); i++) {
        strToConvert[i] = toupper(strToConvert[i]);
    }
    return strToConvert;
}

int main(int ragc, char* argv[]) {
    string line;
    ifstream myfile;
    ifstream dictfile;
    dictfile.open("/var/tmp/twl06.txt");
    string dictionary[DICTSIZE];
    int len[DICTSIZE];
    vector<string> dictvec;
    dictvec.reserve(DICTSIZE);
    vector<string> alreadycheck;

    int i = 0;
    int linelen;
    if (dictfile.is_open()) {
        while (!dictfile.eof()) {
            getline(dictfile, line);
            linelen = line.length();
            if (line[linelen - 1] == '\r') {
                line.erase(linelen - 1);
                --linelen;
            }
            dictionary[i] = line;
            len[i] = linelen;
            dictvec.push_back(line);
            i++;
        }
        dictfile.close();
    }

    myfile.open(argv[1]);
    int score = 0;
    if (myfile.is_open()) {
        getline(myfile, line);
        myfile.close();
        istringstream iss(line);
        vector<string> words;
        copy(istream_iterator<string > (iss),
                istream_iterator<string > (),
                back_inserter<vector<string> >(words));
        int wordscore;
        string check;
        int checklen;
        int lendiff;
        int compared;
        for (int i = 0; i < (int) words.size(); ++i) {
            check = uppercase(words[i]);
            if (binary_search(dictvec.begin(), dictvec.end(), check)) {
                continue;
            }
            checklen = check.length();
            wordscore = INT_MAX;
            for (int d = 0; d < DICTSIZE; ++d) {
                lendiff = abs(checklen - len[d]);
                if (lendiff < wordscore) {
                    compared = checkwords(check, dictionary[d], wordscore);
                    if (compared < wordscore) {
                        wordscore = compared;
                    }
                    if (wordscore == 1) {
                        break;
                    }
                }
            }
            score = score + wordscore;
        }
    }
    printf("%d\n", score);
    return 0;
}
