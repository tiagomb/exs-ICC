#!/bin/bash

METRICA="FLOPS_DP"
CPU=3

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./interpola $1
done


echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 