
## 概述
> computer graphics study
- 纯C语言画图, Milo Yip教学
- openGL学习, 以c++学习
- vulkan 下一步计划

## 过程记录
### 环境背景
1. git 本地仓库与远程仓库关联, 没有共同的history
git pull --allow-unrelated-histories, 一次不行, 根据提示解决

2. c++ 抛开还未入门编程时的那种恐惧心理
- 也无非是源代码, cmake, 再加上系统环境的库, 编译器, 编译器的参数, 编译脚本, 编译成目标文件, 链接成可执行程序, 如此而已

3. gitee 与 github
- commit graph 没有计数, 需要针对每个项目设置本地的 user.email, user.name

4. opengl环境配置
- glut, freeglut, glew 库
- 

### 编译 
1. g++
- 编译
>    g++ -O0 -g3 -Wall -c -fmessage-length=0 -o GL01Hello.o "..\\OpenGL01.cpp" 
- 链接
>    g++ -o GL01Hello.exe GL01Hello.o -lglu32 -lopengl32 -lfreeglut

2. cmake编译
- cmake .. -G "MinGW Makefiles" 
- mingw32-make

3. 调试器 gdb
- 

### 框架
1. 代码复用
- 实现涉及到 glut的代码, 复用, 将每个渲染功能抽象出来
- IRender接口, 像java一样, 根据具体实现, 多态调用对象的渲染函数

2. 模块
> 一个项目, 多个模块, 分别学习:
-  c 语言画图
    * Milo Yip的教学
- openGL学习
    * openGL书籍
- man craft(c语言版)
    * github 上的开源项目
    * man craft demo, 渲染功能, 基本操作已实现

> 命令行编译没问题, 如何在clion上编译不同的模块呢?

### 