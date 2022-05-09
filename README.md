# Working with sysfs, netlink and chardev

## sysfs

Work folder - kbleds. Use `cd kbleds`

The first will be simple module, that control leds on your keyboard.

Main file - kbleds.c, test file - test.sh.

Build the module: 

    $ make

Clean files of module: 

    $ make clean

Install the module: 

    $ sudo insmod kbleds.ko

Check that it exist: 

    $ lsmod | grep kbleds

What is the current value of kbledstatus? Check it: 

    $ cat /sys/kernel/kbleds/kbledstatus 

Set the value of kbledstatus (only for superuser):
    
    $ su - root
    root@your_machine:~# echo <value> > /sys/kernel/kbleds/kbledstatus 
    <value> - number in [0-7]

The meaning of the positions: 1 - CAPS LOCK, 2 - NUM LOCK, 3 - SP.
Options: 0 - turn off, 1 - turn on.

"0. 000   1. 001   2. 010   3. 011   4. 100   5. 101   6. 110   7. 111"

Fast test this module with menu: 

    $ sudo ./test.sh

Remove the module:

    $ sudo rmmod kbleds

Based on this sources:

1. [The Linux Kernel Module Programming Guide,  8 sysfs: Interacting with your module](https://sysprog21.github.io/lkmpg/#sysfs-interacting-with-your-module)

2. [Sysfs read and write module linux kernel 4.15](https://pastebin.com/qEKTZZcB)

3. [Blink keyboard kbleds.c linux kernel 4.15](https://pastebin.com/r46SDJzs)


## chardev

Work folder - chardev. Use `cd chardev`

This is simple example of character device.

Build the module: 

    $ make

Clean files of module: 

    $ make clean

Install the module: 

    $ sudo insmod chardev.ko

Check that it exist: 

    $ lsmod | grep chardev

What is the current value of chardev buffer? Check it: 

    $ sudo cat /dev/chardev

Unfortunately, you can't write in driver, but you can try (only for superuser):
    
    $ su - root
    root@your_machine:~# echo <any_value> > /dev/chardev

Remove the module:

    $ sudo rmmod chardev

Based on this sources:

1. [The Linux Kernel Module Programming Guide,  8 sysfs: Interacting with your module](https://sysprog21.github.io/lkmpg/#sysfs-interacting-with-your-module)

## netlink socket

Work folder - netlink. Use `cd netlink`

This is a client server application. The server is a kernel module, and the client is a user-space program. Communication occurs through a socket with the type AF_NETLINK (communication between kernel and user space).

Build the module of kernel space: 

    $ make

Clean files of module: 

    $ make clean

Install the module: 

    $ sudo insmod kernel_space.ko

Check that it exist: 

    $ lsmod | grep kernel_space

Compile user-space programm: 

    $ make user_space

Now you can launch user-space progamm:

    $ ./user_space

You should write short message, that kernel return you like echo.

Remove the module:

    $ sudo rmmod kernel_space

Based on this sources:

1. [Netlink socket creation](https://stackoverflow.com/questions/27755246/netlink-socket-creation-returns-null)