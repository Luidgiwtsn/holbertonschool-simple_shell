#!/bin/bash

# This script displays the maximum value a PID can reach

# Read the system file that contains the PID limit
if [ -f /proc/sys/kernel/pid_max ]; then
    echo "The maximum PID value on this system is:"
    cat /proc/sys/kernel/pid_max
else
    echo "Unable to find /proc/sys/kernel/pid_max"
    exit 1
fi