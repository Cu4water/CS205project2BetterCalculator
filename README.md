# CS205project2BetterCalculator
一个简单的四则混合计算器，带有变量存储和函数执行功能

在WSL2上可以运行

题目要求：

[![xBsmlD.png](https://s1.ax1x.com/2022/10/16/xBsmlD.png)](https://imgse.com/i/xBsmlD)


实现程度：

[![xBsh7R.md.png](https://s1.ax1x.com/2022/10/16/xBsh7R.md.png)](https://imgse.com/i/xBsh7R)

其中，SCALE=10表示输出结果保留十位小数

额外的项目：实现了对于特定用户的变量储存，加载；在进程中对于变量的输出(ls)

您可以在头文件中查找到每个函数及其作用

较精彩的部分：对于多项式计算，查询优先级最低的运算符，并对左右两侧分别计算，您可以在calc.h和calc.cpp中看到它们

未实现的功能：基于Trie树的变量查找，可以对函数进行if和for操作的函数生成器（脚本执行器）