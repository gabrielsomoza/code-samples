/*
 * File:   main.cpp
 * Author: Gabriel Somoza
 * Email:  me@gabrielsomoza.com
 *
 * Created on January 1, 2011, 2:32 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <math.h>

#define DICT_SIZE 178691

using namespace std;

typedef vector< vector<int> > Tmatrix;

string* read_lines_array(char* filename);
vector<string> read_lines(char* filename);
int main(int, char**);

class Breathalyzer {

private:
    string* dictionary; //to store all words in the dictionary
    vector<string> dictvect; //for quick binary search of correct words
    unsigned int dictlen[DICT_SIZE]; //store the length of each word for heuristics
    string post;

    int lev(string s, string t) {
        int n = s.length(); // length of s
        int m = t.length(); // length of t

        if (n == 0)
            return m;
        else if (m == 0)
            return n;

        int p[n + 1]; //'previous' cost array, horizontally
        int d[n + 1]; // cost array, horizontally
        int *_p = p, *_d = d, *swap; //placeholder to assist in swapping p and d

        char t_j; // jth character of t
        int cost; // cost

        for (int i = 0; i <= n; i++)
            _p[i] = i;

        for (int j = 1; j <= m; j++) {
            t_j = t[j - 1];
            _d[0] = j;
            for (int i = 1; i <= n; i++) {
                cost = s[i - 1] == t_j ? 0 : 1;
                // minimum of cell to the left+1, to the top+1, diagonally left and up +cost
                _d[i] = std::min(std::min(_d[i - 1] + 1, _p[i] + 1), _p[i - 1] + cost);
            }
            // copy current distance counts to 'previous row' distance counts
            swap = _p;
            _p = _d;
            _d = swap;
        }
        // our last action in the above loop was to switch d and p, so p now
        // actually has the most recent cost counts
        return _p[n];
    }

    vector<string> eachWord() {
        istringstream iss(this->post);
        vector<string> tokens;
        copy(istream_iterator<string > (iss),
                istream_iterator<string > (),
                back_inserter<vector<string> >(tokens));
        return tokens;
    }

    string strToUpper(string s) {
        for (int i = 0; s[i] != '\0'; ++i)
            s[i] = toupper(s[i]);
        return s;
    }

public:

    void loadPost(char* input_file) {
        static string dict[DICT_SIZE];
        ifstream dictfile("G:\\Programming\\facebook\\breathalyzer\\twl06.txt");
        string line;

        this->dictvect.reserve(DICT_SIZE);

        unsigned int i = 0;
        int linelen;
        if (dictfile.is_open()) {
            while (getline(dictfile, line)) {
                linelen = line.length();
                if (line[linelen - 1] == '\r') { //important to remove this or else we'll get bad results!
                    line.erase(linelen - 1);
                    --linelen;
                }
                dict[i] = line;
                this->dictlen[i] = linelen;
                this->dictvect.push_back(line);
                i++;
            }
            dictfile.close();
            this->dictionary = dict;
            this->post = this->strToUpper(read_lines(input_file)[0]);
        } else {
            cout << "Failed to open dictionary file!" << endl;
        }
    }

    string analyze() {
        int distance = 0;
        vector<string> words = this->eachWord();
        string word;
        stringstream obuffer; //we use this to convert the number to string

        for (unsigned int i = 0; i < words.size(); ++i) {
            word = words[i];
            //cout << word << endl;
            // if the word exists in the dictionary, number of changes is zero...
            if(binary_search(this->dictvect.begin(), this->dictvect.end(), word))
                continue; //... so just continue with the next word
            distance += this->changes(word);
        }

        obuffer << distance;
        return obuffer.str();
    }

    int changes(string word) {
        int lev, shortest = -1;
        for (unsigned int i = 0; i < DICT_SIZE; ++i) {
            if(shortest > 0 && abs((int)word.length() - (int)this->dictlen[i]) >= shortest)
                continue; //we already know 'lev' will be greater than 'shortest'
            lev = this->lev(word, this->dictionary[i]);
            if (lev == 1) { //because we already did a binary search to check for 0 changes
                shortest = 1;
                break;
            } else if (lev < shortest || shortest < 0)
                shortest = lev;
        }
        return shortest;
    }

    string getPost() {
        return this->post;
    }
};

/*
 * MAIN
 */
int main(int argc, char** argv) {
    Breathalyzer breathalyzer;
    breathalyzer.loadPost(argv[1]);
    cout << breathalyzer.analyze() << endl;
    return 0;
}

/**
 * Reads a file line by line into a string vector
 *
 * @return vector<string> Vector of read lines
 */
vector<string> read_lines(char* filename) {
    ifstream file(filename);
    string line;
    vector<string> lines;

    if (file.is_open()) {
        while (getline(file, line))
            lines.push_back(line);
        file.close();
    } else {
        cout << "Failed to open file!" << endl;
        cout << filename << endl;
    }
    return lines;
}
