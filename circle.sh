#!/bin/bash  
old="xxx"
for file in ./*
    do  
        if test -f $file
        then
            echo ${file#*/}
            if  [ "${file##*.}" = "cif" ]
            then
                new=${file#*/}
                sed -i "s/$old/$new/g" function.c
                gcc -O3 -Wall function.c -o function -lm -fno-stack-protector
                ./function
                old=${file#*/}
                cat cation_pi.dat >> result.dat 
            fi
        fi
    done
sed -i "s/$old/xxx/g" function.c 
rm cation_pi.dat 
