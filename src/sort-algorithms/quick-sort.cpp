#include <iostream>

using namespace std;

void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int partition(int* items, int start, int end) {
    int pivot = items[end];

    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (items[j] < pivot) {
            i++;
            swap(items[i], items[j]);
        }
    }

    i++;
    swap(items[i], items[end]);

    return i;
}

void quick_sort(int* items, int start, int end) {
    /*
     * Time : O(n^2) in worst case, O(n*log n) in avg and best case
     * Space : O(log n)
     */

    if (start < end) {
        int pivot = partition(items, start, end);
        quick_sort(items, start, pivot - 1);
        quick_sort(items, pivot + 1, end);
    }
}

int main() {
    int items[] = {1, 3, 5, 384, 846, 3548, 881};
    quick_sort(items, 0, 6);

    for (int i = 0; i < 6; i++) {
        cout << items[i] << " ";
    }
    cout << endl;

    return 0;
}