#!/bin/bash

echo "export TARGET_BUILD_VARIANT=eng"
export TARGET_BUILD_VARIANT=eng
make
./define
./main.py

echo "export TARGET_BUILD_VARIANT=user"
export TARGET_BUILD_VARIANT=user
make
./define
./main.py

echo "export TARGET_BUILD_VARIANT=userdebug"
export TARGET_BUILD_VARIANT=userdebug
make
./define
./main.py
