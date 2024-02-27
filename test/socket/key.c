#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char input[9];  // 用于保存用户输入的字符串

    printf("请输入8位数字: ");
    scanf("%s", input);
    int len = strlen(input);
    printf("len:%d\n", len);

    // 检查输入是否超过8位
    if (len != 8) {
        printf("密码长度不符合要求，请重新输入\n");
        return 1;
    }

    printf("%ld\n", sizeof(input));

    // 检查输入是否为数字、特殊字符的组合
    int hasSpecialChar = 0;
    for (int i = 0; i < 8; i++) {
        if (input[i] < '0' || input[i] > '9') {
            hasSpecialChar = 1;
            break;
        }
    }

    // 检查是否包含特殊字符
    if (!hasSpecialChar) {
        printf("密码必须包含至少一位特殊字符，请重新输入\n");
        return 1;
    }

    // 输入符合要求
    printf("输入符合要求！\n");

    return 0;
}
