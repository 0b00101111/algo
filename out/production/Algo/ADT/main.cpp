#include <iostream>  // Required for input/output
#include <cstring>   // Required for memset

int main() {
    // define a static array of size 10
    int arr[10] = {};

    // assign values using index
    arr[0] = 1;
    arr[1] = 2;

    // retrieve values using index
    int a = arr[0];

    // Print output for testing
    std::cout << "arr[0]: " << arr[0] << ", arr[1]: " << arr[1] << std::endl;

    return 0;
}
