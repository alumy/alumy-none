# alumy-none

## Brief

alumy-none is an easy-devel library for embedded, it contains the general low level apis for mcu development and inherit other popular 3rd-party libraries.


This library also can be called mcu-sdk, you can use this library to start easy work.

## Prepare
* Ubuntu
 ```
 sudo apt-get -y install gcc-multilib
 ```

## Get Started
* Clone the code
```shell
git clone https://github.com/alumy/alumy-none.git
```
*  Generate Makefile for gcc
```shell
./cmake_gen.sh gcc.cmake Debug 1
```
* make and execute test
```shell
cd build && make && make test
```
## Imporve
If you found bugs, please send mail to 17096226@qq.com, thanks very much.
