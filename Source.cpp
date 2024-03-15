#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ARRAY_SIZE 100
#define FINAL_ARRAY_SIZE 1000

// Data structure for hash node
struct HashNode {
    int keyValue;
    int keyCount;
    int chainIndex; // -1 value indicates not used or end of chain
};

// Linear Open Addressing Hash Table
class LinearOpenHash {

private:
    HashNode linearOpenArray[ARRAY_SIZE];


public:
    // Metric counters array
    int counters[13];
    


    LinearOpenHash() {
        resetCounters();
    }
    


    void resetCounters() {
        for (int i = 0; i < 13; ++i) {
            counters[i] = 0;
        }

        for (int i = 0; i < ARRAY_SIZE; ++i) {
            linearOpenArray[i].keyValue = 0;
            linearOpenArray[i].keyCount = 0;
            linearOpenArray[i].chainIndex = -1;
        }
    }


    int hashFunction(int value) {
        return value % ARRAY_SIZE;
    }



    void linearProbingInsert(int value) {
        int index = hashFunction(value);
        int homeBucket = index;
        int comparisons = 0;

        while (linearOpenArray[index].keyValue != 0) {
            if (linearOpenArray[index].keyValue == value) {
                linearOpenArray[index].keyCount++;
                calculateMetrics(homeBucket, comparisons);
                return;
            }
            index = (index + 1) % ARRAY_SIZE;
            counters[7]++; // Total distance from home (0 if direct insert)
            comparisons++;
        }

        linearOpenArray[index].keyValue = value;
        linearOpenArray[index].keyCount = 1;
        linearOpenArray[index].chainIndex = -1;

        calculateMetrics(homeBucket, comparisons);
    }



    bool search(int value, int& comparisons) {
        int index = hashFunction(value);
        int homeBucket = index;
        comparisons = 0;

        while (linearOpenArray[index].chainIndex != -1) {
            if (linearOpenArray[index].keyValue == value) {
                comparisons++;
                counters[8]++; // Total comparisons
                if (comparisons > counters[9]) {
                    counters[9] = comparisons; // Largest number of comparisons
                }
                if (index == homeBucket) {
                    counters[10]++; // Direct accesses
                }
                else {
                    counters[11]++; // Indirect accesses
                }
                return true;
            }
            index = (index + 1) % ARRAY_SIZE;
            comparisons++;
        }
        return false;
    }



    void printArrays(string testName) {
        cout << "Arrays for Test: " << testName << endl;
        cout << "Linear Open Addressing Array:" << endl;
        cout << "Index    Key Value     Count" << endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            cout << i << "         " << linearOpenArray[i].keyValue << "            " << linearOpenArray[i].keyCount << endl;
        }
    }



    void printMetrics() {
        // Print metrics
    }



    void insertValuesFromFile(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            int value;
            while (file >> value) {
                linearProbingInsert(value);
            }
            file.close();
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }



    void insertRandomValues() {
        srand(time(nullptr));
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            int value = rand() % 10000; // Values between 0 and 9999
            linearProbingInsert(value);
        }
    }



    void calculateMetrics(int homeBucket, int comparisons) {
        counters[0]++; // Total values inserted

        if (comparisons == 0) {
            counters[1]++; // Unique values
            counters[4]++; // Direct inserts
            // Total distance from home for direct inserts will always be 0
        }
        else {
            counters[2]++; // Duplicates
            counters[5]++; // Non-direct inserts
        }

        counters[8] += comparisons; // Total comparisons
        if (comparisons > counters[9]) {
            counters[9] = comparisons; // Largest number of comparisons
        }

        if (comparisons == 0) {
            counters[10]++; // Direct accesses
        }
        else {
            counters[11]++; // Indirect accesses
        }

        if (abs(homeBucket - hashFunction(linearOpenArray[counters[0] - 1].keyValue)) > counters[12]) {
            counters[12] = abs(homeBucket - hashFunction(linearOpenArray[counters[0] - 1].keyValue)); // Largest distance from the home bucket
        }
    }


   
};


int main() {



    // Test the Linear Open Addressing Hash
    LinearOpenHash linearHash;
    linearHash.insertRandomValues();
    linearHash.printArrays("test");
    //linearHash.printMetrics();



    return 0;
}