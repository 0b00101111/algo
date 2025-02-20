#include <iostream>  // Required for input/output
#include <cstring>   // Required for memset
#include <vector>
#include <algorithm>

int main() {
    // define a static array of size 10
    int arr1[10] = {};

    // assign values using index
    arr1[0] = 1;
    arr1[1] = 2;

    // retrieve values using index
    int a = arr1[0];

    // Print output for testing
    std::cout << "arr1[0]: " << arr1[0] << ", arr[1]: " << arr1[1] << std::endl;

    // 创建动态数组，会根据元素数量自动扩缩容
    std::vector<int> arr2;

    for (int i = 0; i < 10; i++) {
        arr2.push_back(i); // O(1)
    }

    // 中间插入元素， O(n)
    arr2.insert(arr2.begin() + 2, 666);

    // 在前端插入，O(1)
    arr2.insert(arr2.begin(), -1);

    // 删除尾端，O(1)
    arr2.pop_back();

    // 在中部删除，O(n)
    arr2.erase(arr2.begin() + 2);

    // 根据索引查元素, O(1)
    int b = arr2[0];

    // 根据索引修改元素, O(1)
    arr2[0] = 100;

    // 根据元素值查索引, O(n)
    auto index = std::find(arr2.begin(), arr2.end(), 666) - arr2.begin();
}
