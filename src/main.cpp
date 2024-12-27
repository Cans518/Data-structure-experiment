#include <iostream>
#include <vector>
#include "heap.hpp"

void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void testHeap(std::vector<int> arr) {
    int heapType = Heap::determineHeapType(arr);

    if (heapType == 0) {
        std::cout << "The sequence is not a heap. \nConverting to a max heap:" << std::endl;
        std::vector<int> max_arr = arr;
        int turns_max = Heap::buildMaxHeap(max_arr);
        printVector(max_arr);
        printf("Number of swaps: %d\n", turns_max);
        std::vector<int> min_arr = arr;
        std::cout << "Converting to a min heap:" << std::endl;
        int turns_min = Heap::buildMinHeap(min_arr);
        printVector(min_arr);
        printf("Number of swaps: %d\n", turns_min);
    } else if (heapType == 1) {
        std::cout << "The sequence is a max heap:" << std::endl;
        printVector(arr);
    } else if (heapType == 2) {
        std::cout << "The sequence is a min heap:" << std::endl;
        printVector(arr);
    }
}

int main() {
    std::vector<int> sequence1 = {100, 86, 48, 73, 35, 39, 42, 57, 66, 21};
    std::vector<int> sequence2 = {12, 70, 33, 65, 24, 56, 48, 92, 86, 33};

    std::cout << "Testing sequence 1:" << std::endl;
    testHeap(sequence1);

    std::cout << "Testing sequence 2:" << std::endl;
    testHeap(sequence2);

    return 0;
}
