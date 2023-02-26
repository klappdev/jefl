# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2019-2023 https://github.com/klappdev

#!/bin/bash

YELLOW_COLOR='\033[1;33m'
GREEN_COLOR='\033[0;32m'
RED_COLOR='\033[0;31m'
NON_COLOR='\033[0m'

LIB_PATH=../bin/jnilibs
JNI_LIB=libjefl.so
MK_FILE=../app/src/main/cpp/Makefile

echo -e "${GREEN_COLOR}Start build ${YELLOW_COLOR}${JNI_LIB} ${GREEN_COLOR}library. ${NON_COLOR}"

if [ ! -d "${LIB_PATH}" ]; then
    echo -e "${RED_COLOR} ${LIB_PATH} directory does not exist. ${NON_COLOR}"
    mkdir -p ${LIB_PATH}
    echo -e "${GREEN_COLOR} Create ${LIB_PATH} directory. ${NON_COLOR}"
fi

if [ ! -f "${MK_FILE}" ]; then
    echo -e "${RED_COLOR} ${MK_FILE} file does not exist. ${NON_COLOR}"
    exit 1
fi

make clean -f ${MK_FILE} && make all -f ${MK_FILE}

echo -e "${GREEN_COLOR}Library ${YELLOW_COLOR}${JNI_LIB} ${GREEN_COLOR}was build success. ${NON_COLOR}"
