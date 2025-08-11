#!/bin/sh
# Affiche la valeur maximale d'un PID sur Linux
if [ -r /proc/sys/kernel/pid_max ]; then
    cat /proc/sys/kernel/pid_max
else
    echo "Cannot read /proc/sys/kernel/pid_max" >&2
    exit 1
fi
