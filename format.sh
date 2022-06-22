#!/bin/bash  
for file in ./*
    do  
        if test -f $file
        then
            echo ${file#*/}
            if  [ "${file##*.}" = "cif" ]
            then
                awk '$1=="ATOM"||$1=="HETATM"{print $0}' $file > $(echo "${file%.*}")_1.cif
                awk '$1=="ATOM"||$4=="MG"{print $0}' $(echo "${file%.*}")_1.cif > $(echo "${file%.*}")_2.cif
		awk '{print $4 " " $11 " " $12 " " $13}' $(echo "${file%.*}")_2.cif > $(echo "${file%.*}")_m.cif
		rm $(echo "${file%.*}")_1.cif
		rm $(echo "${file%.*}")_2.cif
            fi
        fi
    done  
