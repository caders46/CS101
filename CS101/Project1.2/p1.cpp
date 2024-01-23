#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {

    /* Type your code here. */

    ifstream inFS;
    ofstream outFS;
    string identifier;  //filler string
    string source[1000];
    string dest[1000];
    int bandwidth[1000];
    string identifiers[1000];

    int band;           //filler int
    int numlines = 0;

    inFS.open(argv[1]);
    outFS.open(argv[2]); //open both files

    while (!inFS.eof()) { //run through the input file and adds values to arrays
        inFS >> identifier;
        if (identifier == "") { //make sure the end of file hasnt been reached, or "toupper" freaks out
            break;
        }
        for (int j = 0; j < identifier.size(); ++j) {
            identifier.at(j) = toupper(identifier.at(j)); //convert string to uppercase
        }
        source[numlines] = identifier;     //fill array of sources (CAPITALIZED)
        identifier.clear();
        inFS >> identifier;
        if (identifier == "") {
            break;
        }
        for (int j = 0; j < identifier.size(); ++j) {
            identifier.at(j) = toupper(identifier.at(j)); //convert string to uppercase
        }
        dest[numlines] = identifier;       //fill array of destinations (CAPITALIZED)
        identifier.clear();
        inFS >> identifier;
        if (identifier == "") {
            break;
        }
        band = stoi(identifier);    //this gave me too much trouble and i barely remember what it does
        bandwidth[numlines] = band;        //oh yeah it converts file input into an integer to be stored in the array of bandwidths for later use
        identifier.clear();
        numlines++;                        //disgusting for loop behavior
    }

    string unique_identifiers[1000];
    int srcbandwidths[1000];
    int destbandwidths[1000];
    int num_unique_identifiers = 0;

    int index;
    for (int i = 0; i < numlines; ++i) {
        identifier = source[i];
        for (index = 0; !unique_identifiers[index].empty(); ++index) {
            if (identifier == unique_identifiers[index]) {
                break;
            }
        }
        if (index >= num_unique_identifiers) {
            unique_identifiers[num_unique_identifiers] = identifier;
            index = num_unique_identifiers;
            ++num_unique_identifiers;
        }
        srcbandwidths[index] += bandwidth[i];

        identifier = dest[i];
        for (index = 0; !unique_identifiers[index].empty(); ++index) {
            if (identifier == unique_identifiers[index]) {
                break;
            }
        }
        if (index >= num_unique_identifiers) {
            unique_identifiers[num_unique_identifiers] = identifier;
            index = num_unique_identifiers;
            ++num_unique_identifiers;
        }
        destbandwidths[index] += bandwidth[i];
    }

    for (int i = 0; !unique_identifiers[i].empty(); i++) {
        outFS << unique_identifiers[i] << endl;
    }

    outFS << endl;
    outFS << fixed;

    for (int i = 0; !unique_identifiers[i].empty(); i++) {
        if (destbandwidths[i] > 0 && srcbandwidths[i] > 0) {
            outFS << unique_identifiers[i] << " " << srcbandwidths[i] << " " << destbandwidths[i] << " " << setprecision(2) << (double)destbandwidths[i] / (double)srcbandwidths[i] << setprecision(0) << endl;
        }
    }

    outFS.close();
    inFS.close();

    return 0;
}
