## Working with sysfs, netlink and chardev

### sysfs

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

    $ sudo lsmod | grep kbleds

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

    $ rmmod kbleds

Based on this sources:

    1. [The Linux Kernel Module Programming Guide,  8 sysfs: Interacting with your module](https://sysprog21.github.io/lkmpg/#sysfs-interacting-with-your-module)

    2. (Sysfs read and write module linux kernel 4.15)[https://pastebin.com/qEKTZZcB]

    3. (Blink keyboard kbleds.c linux kernel 4.15)[https://pastebin.com/r46SDJzs]

