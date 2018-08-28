
## 概述
> computer graphics study
> 此仓库已经存在两年了, 已经忘了两年前是如何没有走下去, 如今, git 的使用也不成障碍, 图形学的书也读了些, 再一次重拾图形学的学习
- openGL学习, 练习c++
- vulkan 下一步计划

## 过程
1. git 本地仓库与远程仓库关联, 没有共同的history
git pull --allow-unrelated-histories, 一次不行, 根据提示解决

2. c++ 抛开还未入门编程时的那种恐惧心理
- 也无非是源代码, cmake, 再加上系统环境的库, 编译器, 编译器的参数, 编译脚本, 编译成目标文件, 链接成可执行程序, 如此而已

3. gitee 与 github
- commit graph 没有计数, 需要针对每个项目设置本地的 user.email, user.name

3. 环境搞好了, 然也拖了几天 
- 虽然公司的事忙, 找房子也忙, 但是每天还是缺少对图形学的喜爱
- 总得有一两个

## g++ 
1. 编译
- g++ -O0 -g3 -Wall -c -fmessage-length=0 -o GL01Hello.o "..\\OpenGL01.cpp" 

2. 链接
- g++ -o GL01Hello.exe GL01Hello.o -lglu32 -lopengl32 -lfreeglut

3. cmake编译
- cmake .. -G "MinGW Makefiles" 
- mingw32-make

4. 搭建一个渲染框架
- IRender
    * 如何定义接口
- 创建多文件夹
    * cmake使用
- 学习一个现有的项目
    * 在github上找到Craft, 
    * 


