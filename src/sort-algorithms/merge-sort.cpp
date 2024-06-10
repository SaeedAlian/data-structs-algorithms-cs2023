#include <iostream>

using namespace std;

void merge(int* left_array, int* right_array, int* full_array, int left_size, int right_size) {
    int i, j, k = 0;

    while (i < left_size && j < right_size) {
        if (left_array[i] < right_array[j]) {
            full_array[k] = left_array[i];
            i++;

        } else {
            full_array[k] = right_array[j];
            j++;
        }

        k++;
    }

    while (i < left_size) {
        full_array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        full_array[k] = right_array[j];
        j++;
        k++;
    }
}

void merge_sort(int* array, int length) {
    /*
     * Time : O(n*log n)
     * Space : O(n)
     */

    if (length <= 1) return;

    int middle = length / 2;
    int left_array[middle];
    int right_array[length - middle];

    int j = 0;

    for (int i = 0; i < length; i++) {
        if (i < middle) {
            left_array[i] = array[i];
        } else {
            right_array[j] = array[i];
            j++;
        }
    }

    merge_sort(left_array, middle);
    merge_sort(right_array, length - middle);

    merge(left_array, right_array, array, middle, length - middle);
}

int main() {
    int items[] = {1, 3, 5, 384, 3548, 881};
    merge_sort(items, 6);

    for (int i = 0; i < 6; i++) {
        cout << items[i] << " ";
    }
    cout << endl;

    return 0;
}