#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

uint64_t djb2(string str) {
    const char* ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Word {
public:
    string chars;
    vector<int> levels;
    int collisions;


    Word() {}
    Word(string name, int level) {
        chars = name;
        levels.push_back(level);
        collisions = 0;
    }
};

class HashTable {
public:
    vector<Word> table;
    int size;
    int doublehashval;
    int hashtype;
    int numColls;

    HashTable() {
        size = 0;
        doublehashval = 0;
        hashtype = 1;
        numColls = 0;
    }
    HashTable(int s, int pT, int a) {
        size = s;
        hashtype = pT;
        doublehashval = a;
        numColls = 0;
        for (int i = 0; i < s; i++) {
            Word nil("NIL", 0);
            table.push_back(nil);
        }
    }

    void insert(string key, Word entry) {
        int index = djb2(key) % size;
        int originalindex = index;
        int i = 1;
        while (table.at(index % size).chars != "NIL") {
            if (hashtype == 1) {
                
                index++;
                numColls++;
            }
            else if (hashtype == 2) {
                index = originalindex + pow(i, 2);
                i++;
                numColls++;
            }
            else if (hashtype == 3) {
                index += (doublehashval - (djb2(key) % doublehashval));
                numColls++;
            }
            entry.collisions++;
        }
        table.at(index % size) = entry;
    }

    int search(string key) {
        int index = djb2(key) % size;
        int originalindex = index;
        int i = 1;
        while (table.at(index % size).chars != "NIL") {
            if (table.at(index % size).chars == key) {
                return (index % size);
            }
            if (hashtype == 1) {
                index++;
            }
            else if (hashtype == 2) {
                index = originalindex + pow(i, 2);
                i++;
            }
            else if (hashtype == 3) {
                index += (doublehashval - (djb2(key) % doublehashval));
            }
        }
        return -1;
    }
};

int main(int argc, char** argv) {

    int probing;
    int a = NULL;
    string filename = argv[1];
    string filename2 = argv[2];
    int tableSize = stoi(argv[3]);

    string pType = argv[4];

    if (pType == "lp") {
        probing = 1;
    }
    else if (pType == "qp") {
        probing = 2;
    }
    else {
        probing = 3;
    }


    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }
    ifstream file2(filename2);
    if (!file2) {
        cout << "Unable to open " << filename2 << endl;
        return 3;
    }

    if (probing == 3) {
        string fifth = argv[5];
        a = stoi(fifth);
    }

    HashTable HT(tableSize, probing, a);

    string line, line2;
    string tempWord = "";
    char letter;
    int searchResult = 0;
    int level = 1;
    int noWords = 0;
    int uniques = 0;

    while (getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (i == line.size() - 1) {
                if (tempWord != "") {
                    searchResult = HT.search(tempWord);
                    if (searchResult == -1) {
                        Word newEntry(tempWord, level);
                        HT.insert(tempWord, newEntry);
                        uniques++;
                    }
                    else {
                        HT.table.at(searchResult).levels.push_back(level);
                    }
                    noWords++;
                    tempWord = "";
                }
            }
            else {
                if (isalpha(line[i]) && char(line[i]) != ' ') {
                    letter = line[i];
                    tempWord.push_back(tolower(letter));
                }
                else {
                    if (tempWord != "") {
                        searchResult = HT.search(tempWord);
                        if (searchResult == -1) {
                            Word newEntry(tempWord, level);
                            HT.insert(tempWord, newEntry);
                            uniques++;
                        }
                        else {
                            HT.table.at(searchResult).levels.push_back(level);
                        }
                        tempWord = "";
                        noWords++;
                    }
                }
            }
        }
        line = "";
        level++;
    }

    for(int i = 0; i < HT.table.size(); i++){
        cout << i << ": " << HT.table.at(i).chars << endl;
    }

    cout << "The number of words in the file is " << noWords << endl;
    cout << "The number of unique words in the file is " << uniques << endl;
    cout << "The number of total collisions for the table is " << HT.numColls << endl;


    while (getline(file2, line2)) {
        if(line2[line2.size()-1] == '\r'){
            line2.pop_back();
        }
        
        for(int i = 0; i < line2.length(); i++){
            tempWord.push_back(line2[i]);
        }
        
        searchResult = HT.search(tempWord);
        if (searchResult == -1) {
            cout << "Word not found" << endl;
        }
        else {
            cout << line2 << " appears on lines [";
            for (int i = 0; i < HT.table.at(searchResult).levels.size(); i++) {
                if (i != HT.table.at(searchResult).levels.size() - 1) {
                    cout << HT.table.at(searchResult).levels.at(i) << ", ";
                }
                else {
                    cout << HT.table.at(searchResult).levels.at(i) << "]" << endl;
                }
            }
        }
        cout << "The search had " << HT.table.at(searchResult).collisions << " collisions." << endl << endl;
        tempWord = "";
    }

    file.close();
    file2.close();

    return 0;
}