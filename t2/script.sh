#!/bin/bash

#Recebe como parâmetro o arquivo de entrada e usa-o como entrada padrão na execução do programa

CPU=3
METRICA="FLOPS_DP ENERGY"


echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol < $1 | grep  "Sistema\|e-\|e+\|nan\|inf\|MFLOP/s\|Energy \[J\]" | grep -v Runtime
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 
