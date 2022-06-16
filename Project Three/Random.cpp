#include <iostream>
using namespace std;

int other() {
    int stop;
    int result;
    int n;

    cin >> stop;
    result = 0;

    for (n = 0; n < 10; ++n) {
        result += n + 2;
        if (result > stop) {
            cout << "n=" << n;
            cout << endl;
            break;
        }
        cout << result << endl;
    }

    return 0;
}