import java.util.ArrayList;
import java.util.List;


public class main {
  public static void main(String[] args) {
    // define a static array of size 10
    int[] arr = new int[10];

    // assign values using indices
    arr[0] = 1;
    arr[1] = 2;

    // retrieve values using indices
    int a = arr[0];

    System.out.println(a);

    // 创建动态数组，会根据元素数量自动扩缩容
    ArrayList<Integer> arr1 = new ArrayList<>();

    for (int i = 0; i < 10; i++) {
      arr1.add(i);
    }

    // 在中间插入，O(n)
    arr1.add(2, 666);

    // 在头部插入， O(n)
    arr1.add(0, -1);

    // 删除尾部元素, O(1)
    arr1.remove(arr1.size() - 1);

    // 删除中间元素, O(n)
    arr1.remove(2);

    // 查询元素， O(1)
    int b = arr1.get(0);

    // 根据索引修改元素, O(1)
    arr1.set(0, 100);

    // 根据元素值查找索引，O(n)
    int index = arr1.indexOf(666);

    System.out.println(index);
    System.out.println(arr1);
  }
}