#pragma once

#define ARRAY_SIZE 100
#define FINAL_ARRAY_SIZE 1000

using namespace std;


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
    int insertionOrderArray[ARRAY_SIZE]; // Array to store values in the order they were inserted
    int insertionOrderIndex; // Index to track the position in the insertion order array

public:

public:
    // Metric counters array
    int counters[14];



    LinearOpenHash() {
        resetCounters();
        insertionOrderIndex = 0;
    }



    void resetCounters() {
        for (int i = 0; i < 14; i++) {
            this->counters[i] = 0;
        }

        for (int i = 0; i < ARRAY_SIZE; i++) {
            linearOpenArray[i].keyValue = 0;
            linearOpenArray[i].keyCount = 0;
            linearOpenArray[i].chainIndex = -1;
            insertionOrderArray[i] = 0;
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

        if (insertionOrderIndex < ARRAY_SIZE) {
            insertionOrderArray[insertionOrderIndex] = value;
            insertionOrderIndex++;
        }
        else {
            cout << "\nInsertion order array is full." << endl;
        }


    }



    bool search() {
        for (int i = 0; i < insertionOrderIndex; i++) {
            counters[6]++;
            int homeBucket = hashFunction(insertionOrderArray[i]);
            int index = homeBucket;
            int comparisons = 0;

            while (linearOpenArray[index].keyValue != 0) {
                if (comparisons > 1 && index == homeBucket) {
                    std::cout << "\n\nValue " << insertionOrderArray[i] << " not found in hash table.\n\n";
                    break;
                }
                if (linearOpenArray[index].keyValue == insertionOrderArray[i]) {
                    comparisons++;
                    counters[8] += comparisons; // Increment total comparisons
                    if (comparisons > counters[9]) {
                        counters[9] = comparisons; // Largest number of comparisons
                    }
                    if (index == homeBucket) {
                        counters[10]++; // Direct accesses
                    }
                    else {
                        counters[11]++; // Indirect accesses
                    }
                    break; // Break out of the while loop once the value is found
                }
                index = (index + 1) % ARRAY_SIZE;
                comparisons++;
            }
        }

        return true;
    }



    void printArrays(string testName) {
        cout << "Arrays for Test: " << testName << endl;
        cout << "Linear Open Addressing Array:" << endl;
        cout << "Index    Key Value     Count" << endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            cout << i << "         " << linearOpenArray[i].keyValue << "            " << linearOpenArray[i].keyCount << endl;
        }
    }



    void printArrayToFile(string testName) {
        string filename = testName + "_lineararray.txt";
        ofstream outputFile(filename);
        outputFile << "Arrays for Test: " << testName << endl;
        outputFile << "Linear Open Addressing Array:" << endl;
        outputFile << "Index    Key Value     Count" << endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            outputFile << i << "         " << linearOpenArray[i].keyValue << "            " << linearOpenArray[i].keyCount << endl;
        }
    }




};
