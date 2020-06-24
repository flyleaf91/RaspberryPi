#!/usr/bin/env python3

import os

if 'TARGET_BUILD_VARIANT' in os.environ:
    print(os.getenv('TARGET_BUILD_VARIANT'))
