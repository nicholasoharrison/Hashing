#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "LinearOpenHash.h"
#include "ChainedOverflowHash.h"

using namespace std;




void printMetrics(LinearOpenHash l, ChainedOverflowHash c) {
    cout << "          \n\n\n\n                                  Operation Counts";
    cout << "\n                                          Linear                      Chained";
    cout << "\nNumber of key values inserted              "<<l.counters[0] << "                          " << c.counters[0];
    cout << "\n   Unique values                           "<<l.counters[1] << "                          " << c.counters[1];
    cout << "\n   Duplicate values                        "<<l.counters[3] << "                            " << c.counters[3];;
    cout << "\n";
    cout << "\nCollisions";
    cout << "\n   Number of collisions                    "<<l.counters[2] << "                           " << c.counters[2];
    cout << "\n  Distance from home bucket";
    cout << "\n       Number of direct inserts            "<<l.counters[4]<<"   " << (100.0*l.counters[4] / (l.counters[5] + l.counters[4]))<< "%" << "                     " << c.counters[4] << "   " << (100.0 * c.counters[4] / (c.counters[5] + c.counters[4])) << "%";
    cout << "\n       Number of non-direct inserts        "<<l.counters[5]<<"   "<<(100.0*l.counters[5]/(l.counters[5]+l.counters[4])) << "%" << "                     " << c.counters[5] << "   " << (100.0 * c.counters[5] / (c.counters[5] + c.counters[4])) << "%";
    cout << "\n   Average distance from home";
    cout << "\n       Including direct inserts            "<<1.0*l.counters[7]/l.counters[0] << "                        " << 1.0*c.counters[7] / c.counters[0];
    cout << "\n       Not including direct inserts        "<<1.0*l.counters[7]/l.counters[5] << "                      " << 1.0*c.counters[7] / c.counters[5];
    cout << "\n       Largest distance                    "<<l.counters[12]<<" for value: "<<l.counters[13] << "           " << c.counters[12] << " for value: " << c.counters[13];
    cout << "\n";
    cout << "\nSearches";
    cout << "\n   Number of searches                      "<<l.counters[6]<<"                          " << c.counters[6];
    cout << "\n   Number of comparisons";
    cout << "\n       Total number of comparisons         "<<l.counters[8] << "                          " << c.counters[8];
    cout << "\n       Number of direct accesses           "<<l.counters[10]<< "   "<<(100.0 * l.counters[10] / (l.counters[10] + l.counters[11])) << "%" << "                    " << c.counters[10] << "   " << (100.0 * c.counters[10] / (c.counters[10] + c.counters[11])) << "%";
    cout << "\n       Number of indirect accesses         "<<l.counters[11]<< "   "<<(100.0 * l.counters[11] / (l.counters[10] + l.counters[11])) << "%" << "                    " << c.counters[11] << "   " << (100.0 * c.counters[11] / (c.counters[10] + c.counters[11])) << "%";
    cout << "\n       Average number of comparisons       "<<1.0*l.counters[8]/l.counters[6] << "                             " << 1.0*c.counters[8] / c.counters[6];
    cout << "\n       Largest number of comparisons       "<<l.counters[9] << "                            " << c.counters[9];
    cout << "\n\n\n";
}



void printMetricsToFile(const string& testName, LinearOpenHash l, ChainedOverflowHash c) {
    string filename = testName + ".txt";
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << "          \n\n\n\n                                  Operation Counts";
        outputFile << "\n                                          Linear                      Chained";
        outputFile << "\nNumber of key values inserted              " << l.counters[0] << "                          " << c.counters[0];
        outputFile << "\n   Unique values                           " << l.counters[1] << "                          " << c.counters[1];
        outputFile << "\n   Duplicate values                        " << l.counters[3] << "                            " << c.counters[3];;
        outputFile << "\n";
        outputFile << "\nCollisions";
        outputFile << "\n   Number of collisions                    " << l.counters[2] << "                           " << c.counters[2];
        outputFile << "\n  Distance from home bucket";
        outputFile << "\n       Number of direct inserts            " << l.counters[4] << "   " << (100.0 * l.counters[4] / (l.counters[5] + l.counters[4])) << "%" << "                     " << c.counters[4] << "   " << (100.0 * c.counters[4] / (c.counters[5] + c.counters[4])) << "%";
        outputFile << "\n       Number of non-direct inserts        " << l.counters[5] << "   " << (100.0 * l.counters[5] / (l.counters[5] + l.counters[4])) << "%" << "                     " << c.counters[5] << "   " << (100.0 * c.counters[5] / (c.counters[5] + c.counters[4])) << "%";
        outputFile << "\n   Average distance from home";
        outputFile << "\n       Including direct inserts            " << 1.0 * l.counters[7] / l.counters[0] << "                        " << 1.0 * c.counters[7] / c.counters[0];
        outputFile << "\n       Not including direct inserts        " << 1.0 * l.counters[7] / l.counters[5] << "                      " << 1.0 * c.counters[7] / c.counters[5];
        outputFile << "\n       Largest distance                    " << l.counters[12] << " for value: " << l.counters[13] << "           " << c.counters[12] << " for value: " << c.counters[13];
        outputFile << "\n";
        outputFile << "\nSearches";
        outputFile << "\n   Number of searches                      " << l.counters[6] << "                          " << c.counters[6];
        outputFile << "\n   Number of comparisons";
        outputFile << "\n       Total number of comparisons         " << l.counters[8] << "                          " << c.counters[8];
        outputFile << "\n       Number of direct accesses           " << l.counters[10] << "   " << (100.0 * l.counters[10] / (l.counters[10] + l.counters[11])) << "%" << "                    " << c.counters[10] << "   " << (100.0 * c.counters[10] / (c.counters[10] + c.counters[11])) << "%";
        outputFile << "\n       Number of indirect accesses         " << l.counters[11] << "   " << (100.0 * l.counters[11] / (l.counters[10] + l.counters[11])) << "%" << "                    " << c.counters[11] << "   " << (100.0 * c.counters[11] / (c.counters[10] + c.counters[11])) << "%";
        outputFile << "\n       Average number of comparisons       " << 1.0 * l.counters[8] / l.counters[6] << "                             " << 1.0 * c.counters[8] / c.counters[6];
        outputFile << "\n       Largest number of comparisons       " << l.counters[9] << "                            " << c.counters[9];
        outputFile << "\n\n\n";

        outputFile.close();
        cout << "Metrics have been successfully written to the file: " << filename << endl;
    }
    else {
        cout << "Error: Unable to open file " << filename << " for writing." << endl;
    }
}



void insertRandomValues(LinearOpenHash &l, ChainedOverflowHash &c) {
    srand(time(nullptr));
    for (int i = 0; i < (ARRAY_SIZE); i++) {
        int value = rand() % 10000; // Values between 0 and 9999
        l.linearProbingInsert(value);
        c.chainedOverflowInsert(value);
        
    }
}



void insertValuesFromFile(const string& filename, LinearOpenHash &l, ChainedOverflowHash &c) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int value;
            if (!(ss >> value)) {
                cout << "\nError: Non-integer value detected in file." << endl;
                continue; 
            }
            l.linearProbingInsert(value);
            c.chainedOverflowInsert(value);
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }
}


int main() {
    LinearOpenHash linearHash;
    ChainedOverflowHash chainHash;
    char inputChoice;
    cout << "Do you want to input random data (R) or data from a file (F)? ";
    cin >> inputChoice;

    if (inputChoice == 'R' || inputChoice == 'r') {
        insertRandomValues(linearHash, chainHash);
    }
    else if (inputChoice == 'F' || inputChoice == 'f') {
        string filename;
        cout << "Enter the name of the file: ";
        cin >> filename;

        ifstream file(filename);
        if (file.is_open()) {
            insertValuesFromFile(filename, linearHash, chainHash);
            file.close();
        }
        else {
            cout << "Unable to open file " << filename << endl;
            return 1; // Exit with an error code
        }
    }
    else {
        cout << "Invalid input choice. Please choose 'R' for random or 'F' for file." << endl;
        return 1; // Exit with an error code
    }

    // Ask the user for the name of the test being performed
    string testName;
    cout << "\n\nEnter the name of the test: ";
    cin >> testName;

    // Print the arrays to console and text file and perform search
    linearHash.printArrays(testName);
    linearHash.printArrayToFile(testName);
    linearHash.search();
    
    chainHash.printArrays(testName);
    chainHash.printArrayToFile(testName);
    chainHash.search();

    // Print metrics to console and file
    printMetrics(linearHash, chainHash);
    printMetricsToFile(testName, linearHash, chainHash);

    return 0;
}