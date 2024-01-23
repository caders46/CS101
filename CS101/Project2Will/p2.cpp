#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

bool customCompare(const string& str1, const string& str2, const vector<int>& indices) {
    for (int i = 0; i < indices.size(); ++i) {
        int index = indices[i];

        if (index < str1.length() && index < str2.length()) {
            char char1 = str1[index];
            char char2 = str2[index];

            if (char1 < char2) {
                return true;
            } else if (char1 > char2) {
                return false;
            }
        } else if (index < str1.length()) {
            return false;
        } else if (index < str2.length()) {
            return true;
        }
    }

    return str1 < str2;
}

void merge(vector<string>& data, vector<int>& indices, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<string> leftData(n1);
    vector<string> rightData(n2);

    for (int i = 0; i < n1; i++) {
        leftData[i] = data[l + i];
    }

    for (int i = 0; i < n2; i++) {
        rightData[i] = data[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (customCompare(leftData[i], rightData[j], indices)) {
            data[k] = leftData[i];
            i++;
        } else {
            data[k] = rightData[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = leftData[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = rightData[j];
        j++;
        k++;
    }
}

void mergeSort(vector<string>& data, vector<int>& indices, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(data, indices, l, m);
        mergeSort(data, indices, m + 1, r);
        merge(data, indices, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    string datatype = argv[1];
    string sort_fn = argv[2];
    string input_fn = argv[3];
    string output_fn = argv[4];

    if (datatype != "i" && datatype != "s") {
        cout << "Invalid datatype \"" << datatype << "\" (must be \"i\" or \"s\")" << endl;
        return 1;
    }

    ifstream sortF(sort_fn);
    if (!sortF.is_open()) {
        cout << "Unable to open sort file" << endl;
        return 1;
    }

    if (argc != 5) {
        cout << "Usage: ./a.out i|s sort_filename input_filename output_filename" << endl;
        return 1;
    }

    vector<int> sortIndices;
    int index;
    while (sortF >> index) {
        sortIndices.push_back(index);
    }
    sortF.close();

    ifstream inFS(input_fn);
    if (!inFS.is_open()) {
        cout << "Unable to open input file" << endl;
        return 1;
    }

    vector<string> data;
    string value;
    while (inFS >> value) {
        if (datatype == "i") {
            value = string(10 - value.length(), '0') + value;
        }
        data.push_back(value);
    }
    inFS.close();

    mergeSort(data, sortIndices, 0, data.size() - 1);

    ofstream outFS(output_fn);
    if (!outFS.is_open()) {
        cout << "Unable to open output file" << endl;
        return 1;
    }

    for (const string& val : data) {
        if (datatype == "i") {
            size_t pos = val.find_first_not_of('0');
            if (pos != string::npos) {
                outFS << val.substr(pos) << endl;
            } else {
                outFS << "0" << endl;
            }
        } else {
            outFS << val << endl;
        }
    }

    outFS.close();

    return 0;
}
