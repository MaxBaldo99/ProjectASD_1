#include <assert.h>
#include <fstream>
#include "utility.h"
#include "time.h"
#include "chrono"
#include "select.h"

/*
    IMPARA:
    '\n' >>>>>>>>>>>>>>> endl
*/

int main() {
    bool ok = true;
    int k, val, n = 0;
    srand(time(NULL));
    while (ok) {
        n += 50000;
        vector<int> vec(n);
        vec = randomize(n);
        //cin >> vec;
        k = rand() % n + 1;
        val = MOMSelect(&vec[0], 0, vec.size(), k);
        ok = checkSelect(&vec[0], vec.size(), k, val);
        cout << "n: " << n << ", k: " << k << ", val: " << val << ", ok: " << ok << endl;
    }
    return 0;
    
}
