#include <cstdarg>
#include <iostream>
#include <string>
// 至少一个固定参数
int printva(std::string prefix, ...) {
  int num = 0;

  // 声明可变参数列表
  std::va_list ap;

  // 初始化
  va_start(ap, prefix);

  // 假定参数均为int
  int p = 0;
  do {
    p = va_arg(ap, int);
    num += p;
  } while (p != 0);

  va_end(ap);
  std::cout << prefix << num << '\n';
  return num;
}

int main() {
  printva("test", 1, 2, 3, 0);
  printva("test", 1, 2, 0);
}