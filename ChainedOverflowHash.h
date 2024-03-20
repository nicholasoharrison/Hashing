#pragma once

#define ARRAY_SIZE 100

#include <iostream>
#include "HashNode.h"

using namespace std;





// Linear Open Addressing Hash Table Class
class ChainedOverflowHash {

private:
    HashNode mainChainArray[ARRAY_SIZE];
    HashNode overflowArray[ARRAY_SIZE];
    int insertionOrderArray[ARRAY_SIZE]; // Array to store values in the order they were inserted
    int insertionOrderIndex; // Index to track the position in the insertion order array
    bool isFull;
    int overflowIndex;

public:

public:
    // Metric counters array
    int counters[14];



    ChainedOverflowHash() {
        resetCounters();
        isFull = false;
        overflowIndex = 0;
        insertionOrderIndex = 0; // Stores value for where the next open index is in the search queue array
    }

    

    void resetCounters() {
        for (int i = 0; i < 14; i++) {
            this->counters[i] = 0;
        }

        for (int i = 0; i < ARRAY_SIZE; i++) {
            mainChainArray[i].keyValue = 0;
            mainChainArray[i].keyCount = 0;
            mainChainArray[i].chainIndex = -1;
            insertionOrderArray[i] = 0;
            overflowArray[i].keyValue = 0;
            overflowArray[i].keyCount = 0;
            overflowArray[i].chainIndex = -1;
        }
    }


   
    int hashFunction(int value) {
        return value % ARRAY_SIZE;
    }

    

    void chainedOverflowInsert(int value) {
        if (isFull) {
            cout << "\nERROR:  Hash table full!!!";
            return; // Does not proceed to insert if the hash table is full
        }
        int index = hashFunction(value);
        int homeBucket = index;
        int distance = 0;
        int tempIndex;

        if (mainChainArray[homeBucket].keyValue == value) { // Duplicate value found in home bucket
            mainChainArray[homeBucket].keyCount++;
            return;
        }

        if (mainChainArray[homeBucket].keyValue == 0 || (mainChainArray[homeBucket].keyValue == 0 && mainChainArray[homeBucket].keyCount == 0)){ // Direct insert since nothing is in home bucket
            mainChainArray[homeBucket].keyValue = value;
            mainChainArray[homeBucket].keyCount = 1;
            return;
        }
        if (mainChainArray[homeBucket].chainIndex == -1) { // Insert to next value in overflow table since the home bucket does not have any chained
            overflowArray[overflowIndex].keyValue = value;
            overflowArray[overflowIndex].keyCount = 1;
            mainChainArray[homeBucket].chainIndex = overflowIndex;
            overflowIndex++;
            distance++;
            return;
        }
        else {
            index = mainChainArray[homeBucket].chainIndex;
            while (overflowArray[index].chainIndex != -1){
                if (overflowArray[index].keyValue == value) { // Duplicate value found in overflow array
                    overflowArray[index].keyCount++;
                    // Update counters for duplcate found in overflow
                    return;
                }
                distance++;
                tempIndex = index;
                index = overflowArray[tempIndex].chainIndex;
            }
            overflowArray[index].chainIndex = overflowIndex;
            overflowArray[overflowIndex].keyValue = value;
            overflowArray[overflowIndex].keyCount = 1;
            overflowIndex++;

        }

    }

    /*

    bool search() {
        for (int i = 0; i < insertionOrderIndex; i++) {
            counters[6]++; // Total number of searches
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
                    break; // Break out of the while loop once the value is found and go to next value in search queue array
                }
                index = (index + 1) % ARRAY_SIZE; // Wraps arround to beginning of table if > ARRAY_SIZE
                comparisons++;
            }
        }

        return true;
    }

    */


    void printArrays(string testName) {
        cout << "Arrays for Test: " << testName << endl;
        cout << "Chained Overflow Main Array:" << endl;
        cout << "Index    Key Value     Count" << endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            cout << i << "         " << mainChainArray[i].keyValue << "            " << mainChainArray[i].keyCount << "            " << mainChainArray[i].chainIndex << endl;
        }
        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------";
        cout << "Chained Overflow OVERFLOW Array:" << endl;
        cout << "Index    Key Value     Count" << endl;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            cout << i << "         " << overflowArray[i].keyValue << "            " << overflowArray[i].keyCount << "            " << overflowArray[i].chainIndex << endl;
        }
    }

    /*

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

    */




};
