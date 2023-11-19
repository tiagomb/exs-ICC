#!/bin/bash

#Recebe como parâmetro o arquivo de entrada e usa-o como entrada padrão na execução do programa

CPU=3
METRICA="L3 L2CACHE FLOPS_DP"
TAM=(164 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 1000000 10000000 100000000)


echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

file1="resultado"
file2="resultadoOtim"

if [ -f "$file1" ] ; then
	rm "$file1"
fi

if [ -f "$file2" ] ; then
	rm "$file2"
fi

make purge
make ajustePol
make ajustePolOtim

for i in ${TAMS[@]}
do
    ./ajustePol ${i} >> resultado
    ./ajustePolOtim ${i} >> resultadoOtim
done

for i in ${TAMS[@]}
do
    for k in $METRICA
    do
        likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol ${i} | grep -i "L3 bandwidth\|miss \RATIO\|MFLOP/s" | grep -v "Runtime\|GBytes\|rate" | awk {'print $1, $5, $6'} | sed 's/|//g' >> resultado
	    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePolOtim ${i} | grep -i "L3 bandwidth\|miss \RATIO\|MFLOP/s" | grep -v "Runtime\|GBytes\|rate" | awk {'print $1, $5, $6'} | sed 's/|//g' >> resultadoOtim
    done
done

python3 Grafico.py

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 
