# assignment3_1

## TO RUN
```bash
make all
sudo insmod kernel_module.ko
dmesg
```


# assignment3_2

## TO RUN
```bash
make all
sudo insmod mydevice_driver.ko
mknod /dev/mydevice_driver c 25 1
chmod 774 /dev/mydevice_driver
```

## MAJOR NUMBER
Major number 25 is used instead of 250 due to 250 being listed under the output of the command
```bash
cat /proc/devices
```
## TO TEST
Compile the test_device.c and execute the binary with superuser priveleges (Required in case of 774 permission on the device driver)
