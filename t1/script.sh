#!/bin/bash

CPU=3
METRICA="FLOPS_DP ENERGY"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol | grep  "Sistema\|e-\|e+\|nan\|inf\|MFLOP/s\|Energy \[J\]" | grep -v Runtime
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 
