import os
import time

Frequency_HZ = 2

while True:
    os.system('echo 0 > /sys/class/leds/DebugHAT_led/brightness');
    time.sleep(1.0/ Frequency_HZ / 2);
    os.system('echo 1 > /sys/class/leds/DebugHAT_led/brightness');
    time.sleep(1.0/ Frequency_HZ / 2);
