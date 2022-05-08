#!/bin/bash

while [ 1 = 1 ]
    do
        printf "\nThe meaning of the positions: 1 - CAPS LOCK, 2 - NUM LOCK, 3 - SP. \n" 
        printf "Options: 0 - turn off, 1 - turn on \n"
        printf "Menu: \n"
        printf "\t 0. 000 \t 1. 001 \t 2. 010 \t 3. 011 \n"
        printf "\t 4. 100 \t 5. 101 \t 6. 110 \t 7. 111 \n"
        printf "\t 8. default(FF)\t 9. Exit\n"
        read option
        if [ $option == 9 ]
        then 
            break
        fi
        echo $option > /sys/kernel/kbleds/kbledstatus
        echo "Current value: "`cat /sys/kernel/kbleds/kbledstatus` 
        echo "----------------------------------------------------"
    done

echo "Have a nice day :)"