#include <iostream>

using namespace std;

int recursive_binary_search(int* sorted_items, int start, int end, int item) {
    /*
     * Time : O(log n)
     * Space : O(log n)
     */

    if (start == end) {
        if (sorted_items[start] == item) {
            return start;
        } else {
            return -1;
        }
    }

    int mid = (start + end) / 2;

    if (sorted_items[mid] == item) {
        return mid;
    } else if (sorted_items[mid] > item) {
        return recursive_binary_search(sorted_items, start, mid - 1, item);
    } else {
        return recursive_binary_search(sorted_items, mid + 1, end, item);
    }
}

int main() {
    int items[] = {1, 3, 5, 71, 3335};

    cout << recursive_binary_search(items, 0, 5 - 1, 1) << endl;

    return 0;
}