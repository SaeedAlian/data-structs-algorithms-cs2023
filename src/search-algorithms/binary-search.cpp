#include <iostream>

using namespace std;

int binary_search(int* sorted_items, int length, int item) {
    /*
     * Time : O(log n)
     * Space : O(1)
     */

    int start_index = 0;
    int finish_index = length - 1;
    int middle_index;
    int middle_item;

    while (start_index <= finish_index) {
        middle_index = (finish_index - start_index) / 2 + start_index;
        middle_item = sorted_items[middle_index];

        if (middle_item == item) {
            return middle_index;
        } else if (item < middle_item) {
            finish_index = middle_index - 1;
        } else {
            start_index = middle_index + 1;
        }
    }

    return -1;
}

int main() {
    int items[] = {1, 3, 5, 71, 3335};

    cout << binary_search(items, 5, 5) << endl;

    return 0;
}
