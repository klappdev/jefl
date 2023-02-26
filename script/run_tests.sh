# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# 
# Copyright (c) 2019-2023 https://github.com/klappdev

#!/bin/bash

YELLOW_COLOR='\033[1;33m'
GREEN_COLOR='\033[0;32m'
RED_COLOR='\033[0;31m'
NON_COLOR='\033[0m'

LIB_PATH=../bin/jnilibs/
BIN_SRC_PATH=../bin/classes/
BIN_TEST_PATH=../bin/test-classes/

HAMCREST_JAR_PATH=/opt/eclipse/plugins/org.hamcrest.core_1.3.0.v20180420-1519.jar
JUNIT_JAR_PATH=/opt/eclipse/plugins/org.junit_4.13.2.v20211018-1956.jar
JUNIT_MAIN_CLASS=org.junit.runner.JUnitCore

echo -e "${GREEN_COLOR}Start run all ${YELLOW_COLOR}java tests${GREEN_COLOR}. ${NON_COLOR}"

if [ ! -d "${LIB_PATH}" ]; then
    echo -e "${RED_COLOR} ${LIB_PATH} directory does not exist. ${NON_COLOR}"
    mkdir -p ${LIB_PATH}
    echo -e "${GREEN_COLOR} Create ${LIB_PATH} directory. ${NON_COLOR}"
fi

if [ ! -d "${BIN_SRC_PATH}" ]; then
    echo -e "${RED_COLOR} ${BIN_SRC_PATH} directory does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -d "${BIN_TEST_PATH}" ]; then
    echo -e "${RED_COLOR} ${BIN_TEST_PATH} directory does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -f "${HAMCREST_JAR_PATH}" ]; then
    echo -e "${RED_COLOR} ${HAMCREST_JAR_PATH} file does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -f "${JUNIT_JAR_PATH}" ]; then
    echo -e "${RED_COLOR} ${JUNIT_JAR_PATH} file does not exist. ${NON_COLOR}"
    exit 1
fi

java -Djava.library.path=$LIB_PATH -cp $HAMCREST_JAR_PATH:$JUNIT_JAR_PATH:$BIN_TEST_PATH:$BIN_SRC_PATH $JUNIT_MAIN_CLASS org.kl.jefl.FileEraserTest

echo -e "${GREEN_COLOR}All ${YELLOW_COLOR}java tests ${GREEN_COLOR}was finished success. ${NON_COLOR}"


