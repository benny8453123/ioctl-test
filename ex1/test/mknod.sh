#!/bin/bash

ioctl_test_pathname="/dev/ioctl_test"
ioctl_test_devnum=`cat /proc/devices | grep ioctltest | awk '{printf $1}'`

#echo ${ioctl_test_devnum}
#echo ${ioctl_test_pathname}

mknod ${ioctl_test_pathname} c ${ioctl_test_devnum} 0 
