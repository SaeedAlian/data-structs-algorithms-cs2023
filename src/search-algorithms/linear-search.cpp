#include <iostream>

using namespace std;

int linear_search(int* items, int length, int item) {
    /*
     * Time : O(n)
     * Space : O(1)
     */

    for (int i = 0; i < length; i++) {
        if (items[i] == item) {
            return i;
        }
    }

    return -1;
}

int main() {
    int items[] = {1, 3, 5, 71, 3};

    cout << linear_search(items, 5, 5) << endl;

    return 0;
}