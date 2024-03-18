#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "LinearOpenHash.h"

using namespace std;




void printMetrics(LinearOpenHash l) {
    cout << "          \n\n\n\n                                  Operation Counts";
    cout << "\n                                          Linear                      Chained";
    cout << "\nNumber of key values inserted              "<<l.counters[0];
    cout << "\n   Unique values                           "<<l.counters[1];
    cout << "\n   Duplicate values                        "<<l.counters[3];
    cout << "\n";
    cout << "\nCollisions";
    cout << "\n   Number of collisions                    "<<l.counters[2];
    cout << "\n  Distance from home bucket";
    cout << "\n       Number of direct inserts            "<<l.counters[4]<<"   " << (100.0*l.counters[4] / (l.counters[5] + l.counters[4]))<< "%";
    cout << "\n       Number of non-direct inserts        "<<l.counters[5]<<"   "<<(100.0*l.counters[5]/(l.counters[5]+l.counters[4])) << "%";
    cout << "\n   Average distance from home";
    cout << "\n       Including direct inserts            "<<l.counters[7]/l.counters[0];
    cout << "\n       Not including direct inserts        "<<l.counters[7]/l.counters[5];
    cout << "\n       Largest distance                    "<<l.counters[12]<<" for value: "<<l.counters[13];
    cout << "\nSearches";
    cout << "\n   Number of searches                      "<<l.counters[6];
    cout << "\n   Number of comparisons";
    cout << "\n       Total number of comparisons         "<<l.counters[8];
    cout << "\n       Number of direct accesses           "<<l.counters[10]<< "   "<<(100.0 * l.counters[10] / (l.counters[10] + l.counters[11])) << "%";
    cout << "\n       Number of indirect accesses         "<<l.counters[11]<< "   "<<(100.0 * l.counters[11] / (l.counters[10] + l.counters[11])) << "%";
    cout << "\n       Average number of comparisons       "<<l.counters[8]/l.counters[6];
    cout << "\n       Largest number of comparisons       "<<l.counters[9];
    cout << "\n\n\n";
}



void insertRandomValues(LinearOpenHash &l) {
    srand(time(nullptr));
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        int value = rand() % 10000; // Values between 0 and 9999
        l.linearProbingInsert(value);
    }
}



void insertValuesFromFile(string filename, LinearOpenHash &l) {
    ifstream file(filename);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            l.linearProbingInsert(value);
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}



int main() {



    LinearOpenHash linearHash;
    //insertRandomValues(linearHash);
    //insertValuesFromFile("test.txt", linearHash);
    linearHash.printArrays("test");
    linearHash.search();
    printMetrics(linearHash);



    return 0;
}