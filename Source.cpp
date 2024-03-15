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
    int counters[14];
    


    LinearOpenHash() {
        resetCounters();
        counters[13] = 0;
    }
    


    void resetCounters() {
        for (int i = 0; i < 14; i++) {
            this->counters[i] = 0;
        }

        for (int i = 0; i < ARRAY_SIZE; i++) {
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
        int dupValStart = counters[3];

        while (linearOpenArray[index].keyValue != 0) {
            if (linearOpenArray[index].keyValue == value) {
                linearOpenArray[index].keyCount++;
                counters[3]++; // Duplicate values
                counters[0]++;
                //calculateMetrics(homeBucket, comparisons);
                return;
            }
            
            index = (index + 1) % ARRAY_SIZE;
            counters[7]++; // Total distance from home (0 if direct insert)
            comparisons++;
        }

        if (dupValStart == counters[3])
        {
            counters[1]++; //Unique values
        }

        linearOpenArray[index].keyValue = value;
        linearOpenArray[index].keyCount = 1;
        linearOpenArray[index].chainIndex = -1;

        counters[0]++; // Total values inserted

        if (comparisons == 0) {
            counters[4]++; // Direct inserts
        }
        else {
            counters[2]++; // Duplicate of bucket
            counters[5]++; // Non-direct inserts
        }

        if (comparisons > counters[12])
        {
            counters[12] = comparisons;
            counters[13] = linearOpenArray[index].keyValue;
        }

        //calculateMetrics(homeBucket, comparisons);
    }



    bool search(int value, int& comparisons) {
        counters[6]++;
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



  


   
};



void printMetrics(LinearOpenHash l) {
    cout << "          \n\n\n\n    Operation Counts";
    cout << "\n                                          Linear              Chain";
    cout << "\nNumber of key values inserted              "<<l.counters[0];
    cout << "\n   Unique values                           "<<l.counters[1];
    cout << "\n   Duplicate values                        "<<l.counters[3];
    cout << "\n";
    cout << "\nCollisions";
    cout << "\n   Number of collisions                    "<<l.counters[2];
    cout << "\n  Distance from home bucket";
    cout << "\n       Number of direct inserts            "<<l.counters[4];
    cout << "\n       Number of non-direct inserts        "<<l.counters[5];
    cout << "\n   Average distance from home";
    cout << "\n       Including direct inserts            "<<l.counters[7]/l.counters[0];
    cout << "\n       Not including direct inserts        "<<l.counters[7]/l.counters[5];
    cout << "\n       Largest distance                    "<<l.counters[12]<<"  "<<l.counters[13];
    cout << "\nSearches";
    cout << "\n   Number of searches                      "<<l.counters[6];
    cout << "\n   Number of comparisons";
    cout << "\n       Total number of comparisons";
    cout << "\n       Number of direct accesses";
    cout << "\n       Number of indirect accesses";
    cout << "\n       Average number of comparisons";
    cout << "\n       Largest number of comparisons";
}



int main() {



    // Test the Linear Open Addressing Hash
    LinearOpenHash linearHash;
    linearHash.insertRandomValues();
    linearHash.printArrays("test");
    printMetrics(linearHash);



    return 0;
}