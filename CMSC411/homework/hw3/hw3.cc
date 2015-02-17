#include <iostream>

using namespace std;

int main(void) {
    int a[3] = {1, 2, 3};
    int b[3] = {7, 8, 9};

    int dotProduct = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];

    cout << "Dot product of v1 and v2 is: " << dotProduct << "." << endl;
    return 0;
}
