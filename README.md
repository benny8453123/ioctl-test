ioctl-test
===
Learning of using ioctl simply.
These codes are reference from lkmpg: chapter 9 Talking To Device Files

# ex1
## how to test?
### Module part
**get into ex1/ and make first**

1. insmod
`sudo insmod ioctl-test.ko`

2. Check dmesg to make sure insmod is successful
```
...
[179072.849746] [ioctl_test]: ioctltest driver(major: 509) installed.
```

### userspace part
**get into ex1/test/ and make first**

1. Execute mknod.sh with root
`sudo ./mknod.sh`

2. Check nod is exist
```
ben@ben-OptiPlex-7060:/working/ben/module/ioctl-test/ex1/test$ ll /dev | grep ioctl_test
crw-r--r--   1 root root    509,     0  十  14 18:10 ioctl_test
```

3. Start to test: execute test with correct arguments and root permission
`sudo ./test [0-9] [0-9]`
```
ben@ben-OptiPlex-7060:/working/ben/module/ioctl-test/ex1/test$ sudo ./test 5 6
arg0 = 5, arg1 = 6
ioctl_get_val success! arg_get.val = 5
ioctl_get_num_val success! arg_get.val = 6
```

`sudo dmesg`
```
...
[179501.640254] [ioctl_test]: test_ioctl_open call.
[179501.640257] [ioctl_test]: test_ioctl_ioctl call.
[179501.640258] [ioctl_test]: IOCTL_VALSET set val:5 .
[179501.640259] [ioctl_test]: test_ioctl_ioctl call.
[179501.640262] [ioctl_test]: test_ioctl_ioctl call.
[179501.640262] [ioctl_test]: IOCTL_VALSET_NUM set val:6 .
[179501.640263] [ioctl_test]: test_ioctl_ioctl call.
[179501.640284] [ioctl_test]: test_ioctl_close call.

```


# ex2
