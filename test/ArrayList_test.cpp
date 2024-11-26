#include <iostream>
#include "ArrayList.hpp"

// Comparator functions
bool ascendingComparator(const int& a, const int& b) {
    return a < b;
}

bool descendingComparator(const int& a, const int& b) {
    return a > b;
}

int main() {
    // Create an ArrayList and initialize
    ArrayList<int> list = {5, 2, 9, 1, 5, 6};

    std::cout << "Initial list: ";
    list.print();

    // Test insert
    list.insert(2, 10);
    std::cout << "After inserting 10 at index 2: ";
    list.print();

    // Test remove
    list.remove(4);
    std::cout << "After removing element at index 4: ";
    list.print();

    // Test find
    int index = list.find(9);
    std::cout << "Index of element 9: " << index << std::endl;

    // Test get
    int value = list.get(3);
    std::cout << "Element at index 3: " << value << std::endl;

    // Test set
    list.set(3, 15);
    std::cout << "After setting index 3 to 15: ";
    list.print();

    // Test size and capacity
    std::cout << "Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;

    // Test sort (ascending)
    list.sort(ascendingComparator);
    std::cout << "Sorted in ascending order: ";
    list.print();

    // Test sort (descending)
    list.sort(descendingComparator);
    std::cout << "Sorted in descending order: ";
    list.print();

    // Test reverse
    list.reverse();
    std::cout << "After reversing: ";
    list.print();

    // Test clear
    list.clear();
    std::cout << "After clearing: ";
    list.print();
    std::cout << "Size after clearing: " << list.size() << std::endl;

    // Test assignFromArray
    int array[] = {3, 8, 7, 5};
    list.assignFromArray(array, 4);
    std::cout << "After assigning from array: ";
    list.print();

    // Test shrinkToFit
    list.shrinkToFit();
    std::cout << "After shrinkToFit: Capacity: " << list.capacity() << std::endl;

    // Test reserve
    list.reserve(10);
    std::cout << "After reserving capacity 10: Capacity: " << list.capacity() << std::endl;

    return 0;
}
