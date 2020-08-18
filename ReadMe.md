![](https://github.com/SuWeipeng/img/raw/master/13_car/car_16.jpg)

软件介绍
---
> 使用STM32F407VE单片机。            
> 软件高度可移植，原则上各个软件模块 STM32 全系列通用(只要有足够目标模块使用的Flash和RAM既可)。           
> 目前支持两种车型和两种开发板：STM32F407VE 的 Mecanum 四轮车、STM32F103C8 的两轮差速车。

1. 【编程语言】使用 C/C++ 混合编程；
2. 【无线通信】使用 Mavlink 通信协议；
3. 【控制算法】使用 ArduPilot 的 AC_PID 库算法对每个轮进行 PID 控制；
4. 【运动算法】Mecanum 四轮: 按 Mecanum 轮运动学对 4 个麦轮进行动力分配；两轮差速: 按 Mecanum 四轮的方式去掉横移，做两轮差速运动学分解。
5. 【RTOS系统】使用 RT-Thread 实时操作系统进行线程调度；
6. 【LOG 日志】使用 ArduPilot 日志形式记录软件运行的实时数据；       
7. 【文件系统】使用 RT-Thread 虚拟文件系统；       
8. 【nRF24L01】使用 RT-Thread 软件包驱动。

怎样编译
---
一、project generator 使用        

Sugar 只维护配置文件，不维护工程。不同平台的工程可按配置自动生成，方法如下：

1. [一招通吃MDK5、IAR、GCC](https://mp.weixin.qq.com/s/aPUbSAndjvs4CaPj3CFsJg)
2. [【升级】一招通吃MDK5、IAR、GCC](https://mp.weixin.qq.com/s/iVmaQ3S4vcitbJ8iXZyArw)

二、IAR 下的设置（以使用 JLink 调试为例）

![](https://github.com/SuWeipeng/img/raw/master/12_RT-Thread/1_IAR%20%E9%80%89%E7%BC%96%E8%AF%91%E6%96%B9%E5%BC%8F.jpg)

![](https://github.com/SuWeipeng/img/raw/master/12_RT-Thread/2_IAR%20JLink%20%E8%AE%BE%E7%BD%AE.jpg)

![](https://github.com/SuWeipeng/img/raw/master/12_RT-Thread/3_IAR%20JLink%20%E8%AE%BE%E7%BD%AE.jpg)

![](https://github.com/SuWeipeng/img/raw/master/12_RT-Thread/4_IAR%20JLink%20%E8%AE%BE%E7%BD%AE.jpg)

教程推文
---
> 欢迎关注微信公众号：MultiMCU EDU<br>
> ![](https://github.com/SuWeipeng/img/raw/master/17_wechat/08cm.jpg)

一、RTOS:

1. [按需剪裁 RT-Thread 内核的方法](https://mp.weixin.qq.com/s/qzp3cB0SYrPcSGgCGOgwTg)
2. [RT-Thread pin 设备分析](https://mp.weixin.qq.com/s/92eUSYIHWP6YKjDDM_8XOw)
3. [rt-thread 与 C++ 的美满姻缘](https://mp.weixin.qq.com/s/dxdBfF1ov-wOngM8Eqm4BQ)
4. [RT-Thread mavlink 甜蜜相拥教程](https://mp.weixin.qq.com/s/ak7_PFfcDl25FjdYzgjZdA)
5. [RT-Thread 野生单步调试法](https://mp.weixin.qq.com/s/qXWS6dqgTLgIxhhX60P8zA)
6. [RT-Thread 自制 Linux IDE](https://mp.weixin.qq.com/s/sxWvwG1uNx042l72qpFsxQ)
7. [怎样快速把 4 个按键玩儿出 12 种甚至更多效果](https://mp.weixin.qq.com/s/1wkgGLGHLF1hVMsapwEWFQ)
8. [RT-Thread 当前最新的 nRF24L01 组件这么用](https://mp.weixin.qq.com/s/0CQSuQMWr0RIKG23EPWUug)

二、车控：
1. [一起来做遥控车（软件架构训练三）](https://mp.weixin.qq.com/s/lSt9VkPxJicPCiQhRn3p7A)
2. [马达驱动](https://mp.weixin.qq.com/s/7Bk-xQbymZaez4g5sUALxw)
3. [物联网通信，如何应用 mavlink 通信协议](https://mp.weixin.qq.com/s/K92U5lO0KGM4mUzyGSXvcg)
4. [让车听遥控的话](https://mp.weixin.qq.com/s/h7FURP4kGNTJmfsHatk-4A)
5. [看完这篇一定能会用 ab 相编码器](https://mp.weixin.qq.com/s/aUa0sHmGF6CbPej6O9IzKQ)
6. [PID 调参](https://mp.weixin.qq.com/s/TO926HglAhvM9RNe-2kJuQ)
7. [在 MCU 上使用 C++ 系列之类](https://mp.weixin.qq.com/s/TBuNjP33tg1pKDBF3gwy7Q)
8. [在 MCU 上使用 C++ 系列之模板类](https://mp.weixin.qq.com/s/Ye3Yh8cH5bzmuaq9ub90ow)
9. [在 MCU 上使用 C++ 之模板类进阶与线性 Kalman 算法代码](https://mp.weixin.qq.com/s/qmRwsDrzu2y2nKsxqZq8oA)

三、不同车型

通过前后台架构兼容不同车型，不同车型在不同的 branch 上。

![](https://github.com/SuWeipeng/img/raw/master/13_car/github_01.jpg)

有关“前后台架构”请看：

1. [一文读懂 ArduPilot 的前后台架构](https://mp.weixin.qq.com/s/VQlkTsTn4in7eq3V7XF4ew)
2. [一文实现 ArduPilot 的前后台架构](https://mp.weixin.qq.com/s/r_nJiAEgwNnjKPqRkDmvxg)