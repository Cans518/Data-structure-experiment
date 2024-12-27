#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include <algorithm>

namespace Heap {

/**
 * @brief 判断数组是最大堆、最小堆还是都不是。
 * 
 * @param arr 输入数组。
 * @return 0 表示不是堆，1 表示最大堆，2 表示最小堆。
 */
int determineHeapType(const std::vector<int>& arr) {
    int n = arr.size();
    bool isMax = true;
    bool isMin = true;

    for (int i = 0; i <= (n - 2) / 2; ++i) {
        if (2 * i + 1 < n) {
            if (arr[i] < arr[2 * i + 1]) isMax = false;
            if (arr[i] > arr[2 * i + 1]) isMin = false;
        }
        if (2 * i + 2 < n) {
            if (arr[i] < arr[2 * i + 2]) isMax = false;
            if (arr[i] > arr[2 * i + 2]) isMin = false;
        }
    }

    if (isMax) return 1;
    if (isMin) return 2;
    return 0;
}

/**
 * @brief 调整为最大堆属性。
 * 
 * @param arr 输入数组。
 * @param n 堆的大小。
 * @param i 需要堆化的索引。
 * @return 执行的交换次数。
 */
int heapifyMax(std::vector<int>& arr, int n, int i) {
    int swaps = 0;
    while (true) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            swaps++;
            i = largest;
        } else {
            break;
        }
    }
    return swaps;
}

/**
 * @brief 调整为最小堆属性。
 * 
 * @param arr 输入数组。
 * @param n 堆的大小。
 * @param i 需要堆化的索引。
 * @return 执行的交换次数。
 */
int heapifyMin(std::vector<int>& arr, int n, int i) {
    int swaps = 0;
    while (true) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] < arr[smallest]) smallest = left;
        if (right < n && arr[right] < arr[smallest]) smallest = right;

        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            swaps++;
            i = smallest;
        } else {
            break;
        }
    }
    return swaps;
}

/**
 * @brief 将数组转换为最大堆。
 * 
 * @param arr 输入数组。
 * @return 执行的交换次数。
 */
int buildMaxHeap(std::vector<int>& arr) {
    int n = arr.size();
    int swaps = 0;
    for (int i = n / 2 - 1; i >= 0; --i) {
        swaps += heapifyMax(arr, n, i);
    }
    return swaps;
}

/**
 * @brief 将数组转换为最小堆。
 * 
 * @param arr 输入数组。
 * @return 执行的交换次数。
 */
int buildMinHeap(std::vector<int>& arr) {
    int n = arr.size();
    int swaps = 0;
    for (int i = n / 2 - 1; i >= 0; --i) {
        swaps += heapifyMin(arr, n, i);
    }
    return swaps;
}

}

#endif // HEAP_HPP
