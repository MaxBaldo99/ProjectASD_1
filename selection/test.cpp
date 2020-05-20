#include <assert.h>
#include <fstream>
#include "utility.h"
#include "select.h"
#include "time.h"


int main() {
    /*
    int k, val = 0;
    vector<int> vec;
    cin >> vec;
    cin >> k;
    val = MOMSelectIterative(&vec[0], 0, vec.size(), k);
    cout << val << endl;
    */
    
    bool ok = true;
    int k, val, n = 0;
    srand(time(NULL));
    while (n < 5 * pow(10, 6)) {
        n += 50000;
        vector<int> vec(n);
        vec = randomize(n);
        k = rand() % n + 1;
        val = MOMSelect(vec, 0, vec.size(), k);
        ok = checkSelect(&vec[0], vec.size(), k, val);
        cout << "n: " << n << ", k: " << k << ", val: " << val << ", ok: " << ok << endl;
    }
    
    return 0;
    
}