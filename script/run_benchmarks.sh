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

JMH_CORE_JAR_PATH=~/.gradle/caches/modules-2/files-2.1/org.openjdk.jmh/jmh-core/1.36/5a69117788322630fc5f228bc804771335d41b1b/jmh-core-1.36.jar
JMH_ANNO_GEN_JAR_PATH=~/.gradle/caches/modules-2/files-2.1/org.openjdk.jmh/jmh-generator-annprocess/1.36/41c92c483f92b3cce1c01edd849bfd3ffd920cf6/jmh-generator-annprocess-1.36.jar
JOPT_JAR_PATH=~/.gradle/caches/modules-2/files-2.1/net.sf.jopt-simple/jopt-simple/5.0.4/4fdac2fbe92dfad86aa6e9301736f6b4342a3f5c/jopt-simple-5.0.4.jar

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}

echo -e "${GREEN_COLOR}Start run all ${YELLOW_COLOR}java benchmarks${GREEN_COLOR}. ${NON_COLOR}"

if [ ! -d "${LIB_PATH}" ]; then
    echo -e "${RED_COLOR} ${LIB_PATH} directory does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -d "${BIN_SRC_PATH}" ]; then
    echo -e "${RED_COLOR} ${BIN_SRC_PATH} directory does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -d "${BIN_TEST_PATH}" ]; then
    echo -e "${RED_COLOR} ${BIN_TEST_PATH} directory does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -f "${JMH_CORE_JAR_PATH}" ]; then
    echo -e "${RED_COLOR} ${JMH_CORE_JAR_PATH} file does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -f "${JMH_ANNO_GEN_JAR_PATH}" ]; then
    echo -e "${RED_COLOR} ${JMH_ANNO_GEN_JAR_PATH} file does not exist. ${NON_COLOR}"
    exit 1
fi

if [ ! -f "${JOPT_JAR_PATH}" ]; then
    echo -e "${RED_COLOR} ${JOPT_JAR_PATH} file does not exist. ${NON_COLOR}"
    exit 1
fi

java -Djava.library.path=$LIB_PATH -cp $JOPT_JAR_PATH:$JMH_CORE_JAR_PATH:$JMH_ANNO_GEN_JAR_PATH:$BIN_TEST_PATH:$BIN_SRC_PATH org.kl.jefl.FileEraserBenchmark

echo -e "${GREEN_COLOR}All ${YELLOW_COLOR}java benchmarks ${GREEN_COLOR}was finished success. ${NON_COLOR}"
