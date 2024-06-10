#include <iostream>

using namespace std;

void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void selection_sort(int* items, int length) {
    /*
     * Time : O(n^2)
     * Space : O(1)
     */

    if (length < 2) return;

    int min;

    for (int i = 0; i < length; i++) {
        min = i;

        for (int j = i; j < length; j++) {
            if (items[j] < items[min]) {
                min = j;
            }
        }

        if (i != min) {
            swap(items[i], items[min]);
        }
    }
}

int main() {
    int items[] = {1, 3, 5, 71, 3, 516, 584, 6, 384, 35, 3548, 35, 1, 2, 3, 5, 4, 5, 68, 7, 9, 8, 3, 881};
    selection_sort(items, 24);

    for (int i = 0; i < 24; i++) {
        cout << items[i] << " ";
    }
    cout << endl;

    return 0;
}