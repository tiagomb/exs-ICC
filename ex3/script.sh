#!/bin/bash

METRICA="FLOPS_DP"
CPU=3

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make all removeObjects

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./interpola $1 | grep -i "e-\|e+\|mflop/s" | grep -v Runtime | awk {'print $1, $5, $6'}> resultado
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 