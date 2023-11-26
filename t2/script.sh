#!/bin/bash

#Recebe como parâmetro o arquivo de entrada e usa-o como entrada padrão na execução do programa

CPU=3
METRICA="FLOPS_DP L3 L2CACHE"
TAM=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 1000000 10000000 100000000)


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

for i in ${TAM[@]}
do
    ./gera_entrada ${i} | ./ajustePol >> resultado
    ./gera_entrada ${i} | ./ajustePolOtim ${i} >> resultadoOtim
done

for i in ${TAM[@]}
do
    for k in $METRICA
    do
        ./gera_entrada ${i} | likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol | grep -i "L3 bandwidth\|miss \RATIO\|MFLOP/s" | grep -v "Runtime\|GBytes\|rate" | awk {'print $1, $5, $6'} | sed 's/|//g' >> resultado
	./gera_entrada ${i} | likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePolOtim | grep -i "L3 bandwidth\|miss \RATIO\|MFLOP/s" | grep -v "Runtime\|GBytes\|rate" | awk {'print $1, $5, $6'} | sed 's/|//g' >> resultadoOtim
    done
done

python3 Grafico.py

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 
