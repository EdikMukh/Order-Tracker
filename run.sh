#!/bin/bash
g++ ./src/main.cpp \
    \./src/utils/file_utils.cpp \
    \./src/ui/handlers/add_order.cpp \
    \-o./build/order_tracker && ./build/order_tracker.exe
