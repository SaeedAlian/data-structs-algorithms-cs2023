#include <iostream>

using namespace std;

void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void bubble_sort(int* items, int length) {
    /*
     * Time : O(n^2)
     * Space : O(1)
     */

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i; j++) {
            if (items[j] > items[j + 1]) {
                swap(&items[j + 1], &items[j]);
            }
        }
    }
}

int main() {
    int items[] = {1, 3, 5, 384, 3548, 881};
    bubble_sort(items, 6);

    for (int i = 0; i < 6; i++) {
        cout << items[i] << " ";
    }
    cout << endl;

    return 0;
}
