#include <stdio.h>
#include <stdlib.h>
/* 在上面的代码中，我们定义了一个 set_value 函数，该函数接受一个二级指针 ptr 的地址和一个整数 value。
在函数内部，我们首先使用 malloc 分配了一个整数大小的内存，并将其地址赋值给二级指针 *ptr。
然后，我们使用间接引用操作符 **ptr 将 value 的值赋给这个内存位置。
在 main 函数中，我们首先定义了一个一级指针 ptr 并初始化为 NULL。
然后，我们调用 set_value 函数，并传递 ptr 的地址以及要设置的值 value。
由于我们想在函数中修改 ptr 的值，因此我们需要传递 ptr 的地址。最后，我们打印出 ptr 指向的值。 */
void allocate(int **arr, int n) {
    *arr = (int*) malloc(n * sizeof(int));
}

void set_value(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 10;
    int *arr;
    allocate(&arr, n);
    set_value(arr, n);
    print_array(arr, n);
    free(arr);
    return 0;
}
