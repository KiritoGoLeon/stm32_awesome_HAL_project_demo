# stm32 HAL project demo

KE基本架构

<img src="readme.assets/image-20201205114403073.png" alt="image-20201205114403073" style="zoom:33%;" />

分为了APL,BLL,FML,HDL,BSP,HARDWARE

如果是stm32使用cubemx和HAL库开发, HAL库本身就是兼容F0 F1 F4等型号, 可以看作BSP层, 同时HAL库又提供了内部的的驱动，所以HAL库是包括了BSP和部分HDL层的．

## KE架构在stm32的应用

![image-20201205114813442](readme.assets/image-20201205114813442.png)

![image-20201205115043258](readme.assets/image-20201205115043258.png)