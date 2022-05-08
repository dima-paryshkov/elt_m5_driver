## Working with sysfs, netlink and chardev

### sysfs

The first will be simple module, that control leds on your keyboard.

Main file - kbleds.c
Test file - test.sh

Build the module: 

    make

Clean file of module: 

    make clean

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

The meaning of the positions: 1 - CAPS LOCK, 2 - NUM LOCK, 3 - SP
Options: 0 - turn off, 1 - turn on
"0. 000 \t 1. 001 \t 2. 010 \t 3. 011"
"4. 100 \t 5. 101 \t 6. 110 \t 7. 111"

Fast test this module with menu: 

    $ sudo ./test.sh

Remove the module:

    rmmod kbleds
