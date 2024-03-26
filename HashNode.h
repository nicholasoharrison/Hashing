#pragma once

#define ARRAY_SIZE 100

// Data structure for hash node
struct HashNode {
    int keyValue;
    int keyCount;
    int chainIndex; // -1 value indicates not used or end of chain
};
