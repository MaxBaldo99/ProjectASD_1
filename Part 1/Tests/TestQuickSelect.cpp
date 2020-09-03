#include <iostream>
#include "select.h"

int main() {
    vector<int> vec;
    int k;
    cin >> vec;
    cin >> k;
    cout << quickSelect(vec, 0, vec.size(), k) << endl;
    return 0;
}