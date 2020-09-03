#include <iostream>
#include "select.h"

int main() {
    vector<int> vec;
    int k;
    cin >> vec;
    cin >> k;
    cout << MOMSelect(vec, 0, vec.size(), k) << endl;
    return 0;
}