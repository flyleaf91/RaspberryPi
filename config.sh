#!/bin/bash

# led pre config
cd /sys/class/gpio
echo 10 > export
cd gpio10
echo out > direction

# button pre config
cd /sys/class/gpio
echo 9 > export
cd gpio9
echo both > edge
