# FormalLangSimulator

## 软件依赖

本框架依赖于cmake进行编译，需安装3.13.0以上版本的cmake方可使用。

## 使用方法

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

### 项目细节
- `pda` 模拟器采用了直观的栈模拟，主体由 `pda.parser` 和 `pda` 组成
- `tm` 模拟器采用了双端队列 `deque` 模拟双向无穷的磁带，主体由 `tm.parser` 和 `tm` 组成
- `verbose` 模式下，会输出每一步的状态，方便调试
- `cli_parser` 用于解析命令行参数


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

