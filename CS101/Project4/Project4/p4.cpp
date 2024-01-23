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

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    Person(string i, string f, string l, string e, string p, string c, string s, string pC) {
        id = i;
        first = f;
        last = l;
        email = e;
        phone = p;
        city = c;
        state = s;
        postalCode = pC;
    }
};



class HashTable {
public:
    vector<vector<Person>> table;
    int size;
    string thiskey;

    HashTable(int tablesize) {
        size = tablesize;
        for (int i = 0; i < tablesize; i++) {
            vector<Person> v1;
            
            table.push_back(v1);
        }
    }

    void insert(Person p1, string str, string key) {
        int index = djb2(str) % size;
        int originalindex = index;
        if (table.at(index).size() == 0) {
            table.at(index).push_back(p1);
        }
        else {
            if (key == "Id") {
                if (table.at(index).at(0).id == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i*i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "FirstName") {
                if (table.at(index).at(0).first == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "LastName") {
                if (table.at(index).at(0).last == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "Email") {
                if (table.at(index).at(0).email == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "Phone") {
                if (table.at(index).at(0).phone == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "City") {
                if (table.at(index).at(0).city == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "State") {
                if (table.at(index).at(0).state == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
            else if (key == "PostalCode") {
                if (table.at(index).at(0).postalCode == str) {
                    table.at(index).push_back(p1);
                }
                else {
                    for (int i = 0; i < size; i++) {
                        index = originalindex + i + i * i;
                        if (index > size - 1) {
                            index = index - size;
                        }
                        if (table.at(index).size() == 0) {
                            break;
                        }
                    }
                    table.at(index).push_back(p1);
                }
            }
        }
    }

    void search(string query, string key) {
        int index = djb2(query) % size;
        int originalindex = index;
        bool found = false;
        int j = 0;
        if (key == "Id") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).id == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "FirstName") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).first == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "LastName") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).last == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "Email") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).email == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "Phone") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).phone == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "City") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).city == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "State") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).state == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
        else if (key == "PostalCode") {
            while (table.at(index).size() != 0 && j < size) {
                if (table.at(index).at(0).postalCode == query) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    for (int i = 0; i < table.at(index).size(); i++) {
                        cout << table.at(index).at(i).id << "," << table.at(index).at(i).first << "," << table.at(index).at(i).last << "," << table.at(index).at(i).email << "," << table.at(index).at(i).phone << "," << table.at(index).at(i).city << "," << table.at(index).at(i).state << "," << table.at(index).at(i).postalCode << endl;
                    }
                    found = true;
                    break;
                }
                else {
                    j++;
                    index = (originalindex + j + j * j) % size;
                }
            }
            if (!found) {
                cout << "No results" << endl;
            }
        }
    }

};

void getVal(istream& is, string& str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string& key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }

    HashTable hashbrowns(tableSize);
    hashbrowns.thiskey = key;
    string id, first, last, email, phone, city, state, postalCode;

    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, token, '\t');
        id = token;
        getline(iss, token, '\t');
        first = token;
        getline(iss, token, '\t');
        last = token;
        getline(iss, token, '\t');
        email = token;
        getline(iss, token, '\t');
        phone = token;
        getline(iss, token, '\t');
        city = token;
        getline(iss, token, '\t');
        state = token;
        getline(iss, token, '\t');
        postalCode = token;

        Person p1(id, first, last, email, phone, city, state, postalCode);

        if (key == "Id") {
            hashbrowns.insert(p1, p1.id, key);
        }
        else if (key == "FirstName") {
            hashbrowns.insert(p1, p1.first, key);
        }
        else if (key == "LastName") {
            hashbrowns.insert(p1, p1.last, key);
        }
        else if (key == "Email") {
            hashbrowns.insert(p1, p1.email, key);
        }
        else if (key == "Phone") {
            hashbrowns.insert(p1, p1.phone, key);
        }
        else if (key == "City") {
            hashbrowns.insert(p1, p1.city, key);
        }
        else if (key == "State") {
            hashbrowns.insert(p1, p1.state, key);
        }
        else if (key == "PostalCode") {
            hashbrowns.insert(p1, p1.postalCode, key);
        }
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            // print code here
            for (int i = 0; i < hashbrowns.table.size(); i++) {
                if (hashbrowns.table.at(i).size() != 0) {
                    cout << i << ": ";
                    if (key == "Id") {
                        cout << hashbrowns.table.at(i).at(0).id << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "FirstName") {
                        cout << hashbrowns.table.at(i).at(0).first << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "LastName") {
                        cout << hashbrowns.table.at(i).at(0).last << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "Email") {
                        cout << hashbrowns.table.at(i).at(0).email << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "Phone") {
                        cout << hashbrowns.table.at(i).at(0).phone << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "City") {
                        cout << hashbrowns.table.at(i).at(0).city << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "State") {
                        cout << hashbrowns.table.at(i).at(0).state << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    else if (key == "PostalCode") {
                        cout << hashbrowns.table.at(i).at(0).postalCode << " (" << hashbrowns.table.at(i).size() << "),";
                    }
                    cout << endl;
                }
            }
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            // lookup code here
            hashbrowns.search(val, key);
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
