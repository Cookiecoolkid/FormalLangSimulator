# FormalLangSimulator

## 软件依赖

本框架依赖于cmake进行编译，需安装3.13.0以上版本的cmake方可使用。

## 编译方法

本框架的使用方法为：

1. 在工程根目录处，使用指令`cmake -B build`
2. 在工程根目录处，使用指令`cd ./build; make`

测试框架将使用上述方法对工程进行编译。执行完毕后，在工程根目录下应当出现`/bin`文件夹，其中含有可执行文件`fla`，测试框架将对该可执行文件进行测试。

## 关于实验

### 项目结构

```
.
├── CMakeLists.txt
├── fla-project
│   ├── automata.h
│   ├── cli_parser.cpp
│   ├── cli_parser.h
│   ├── main.cpp
│   ├── parser.cpp
│   ├── parser.h
│   ├── pda.cpp
│   ├── pda.h
│   ├── pda_parser.cpp
│   ├── pda_parser.h
│   ├── tm.cpp
│   ├── tm.h
│   ├── tm_parser.cpp
│   ├── tm_parser.h
│   └── verbose.cpp
├── pda
│   ├── anbn.pda
│   └── case.pda
├── README.md
├── tm
│   ├── case1.tm
│   ├── case2.tm
│   └── palindrome_detector_2tapes.tm
└── 实验手册.pdf
```

(提交的 .zip 文件去除了示例的 `anbn.pda`, `palindrome_detector_2tapes.tm` 以及实验手册)

### 项目说明
```bash
cd bin
./fla -h
usage:    fla [-h|--help] <pda|tm> <input>
          fla [-v|--verbose] [-h|--help] <tm> <input>
```

- 其中输入为 `pda` 或 `tm`，分别对应 PDA 和 TM 的模拟器，其定义格式请参考实验手册
- TM/PDA 均提供了 `verbose` 模式查看详细运行过程
- `input` 为输入文件的路径，输入文件的格式请参考实验手册
- 本实验对于手册中的要求均已实现，并且增加了 `pda` 的 `verbose` 模式

### 设计思路
- `pda` 模拟器采用了直观的栈模拟，主体由 `pda.parser` 和 `pda` 组成
- `tm` 模拟器采用了双端队列 `deque` 模拟双向无穷的磁带，主体由 `tm.parser` 和 `tm` 组成
- `verbose` 模式下，会输出每一步的状态，方便调试
- `cli_parser` 用于解析命令行参数

### 问题/解决
- `pda` 和 `tm` 模拟器的实现较为直观，按照规范读取输入/纸带，模拟状态转移即可
- 较为困难的是 `.pda` 和 `.tm` 文件编写，需要按照规范书写，其中 `case2.tm` 较为复杂，模拟的是如下函数：
```cpp
bool isSqrt(int n) {
    for(int i = 1; n > 0; i += 2) n -= i;
    return 0 == n;
}
```
其中的循环体分为多个步骤，`case2.tm` 中采用三条纸带来实验，循环过程中第一、二条纸带分别存储 `i, n`，第三条纸带实际上是作为第二条纸带的 `track` 来使用(在 `n -= i` 的过程中会进位，此时要标记开始进位的位置以便于下次回到标记继续执行)，最终判断 `n` 是否为 `0` 或是否为负数即可(本实验采用补码运算，相减的时候会对 `i` 做 `flip, plus one` 的操作)

- 在每次循环的开始，都会进行 `align` 操作，即将第一、二条纸带的 `head` 对齐，同时都拓展一位最高位补 `0`(此时均为正数)，以便于后续补码运算中进位符号位的处理，这是我认为设计过程处理最关键的地方，这使得后续的判断负数 / 0 变得十分简单，只要检查最高位是否为 `1` 或者是否为全 `0` 即可.

### 总结感想
这是一次非常有意义的实验，实验中学习并且加深到了很多关于 `PDA` 和 `TM` 的知识，并且感受到 `CSer`将理论变为实践的乐趣，这真的太 `coooooool` 了！

### 测试用例

对于 `pda`，以括号匹配为例，测试用例为：
```bash
$ ./bin/fla -v ./pda/case.pda "(()())"
Input: (()())
==================== RUN ====================
Step  : 0
State : q0
Read  : (
Stack : z 
---------------------------------------------
Step  : 1
State : q1
Read  : (
Stack : a z 
---------------------------------------------
Step  : 2
State : q1
Read  : )
Stack : a a z 
---------------------------------------------
Step  : 3
State : q1
Read  : (
Stack : a z 
---------------------------------------------
Step  : 4
State : q1
Read  : )
Stack : a a z 
---------------------------------------------
Step  : 5
State : q1
Read  : )
Stack : a z 
---------------------------------------------
Step  : 6
State : q1
Read  : _
Stack : z 
---------------------------------------------
Step  : 7
State : accept
Read  : _
Stack : 
---------------------------------------------
Result: true
==================== END ====================
```

对于 `tm`，以判断输入`1`的个数是否为平方数为例(过程较长这里没有使用 `verbose` 模式)，测试用例为：
```bash
$ ./bin/fla ./tm/case2.tm "111111111"
true
```

