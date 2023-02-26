JAVA_DIR = ../app/src/main/java
CPP_DIR = ../app/src/main/cpp
CPP_INC_DIR = ../app/src/main/cpp
BIN_JAVA_DIR = ../bin/classes
BIN_CPP_DIR = ../bin/jnilibs

CXX=g++
CXXFLAGS = -std=c++20 -g -O0
CXX_LIBS = -lstdc++fs

CXX_OBJS = $(BIN_CPP_DIR)/LoadLibrary.o \
		   $(BIN_CPP_DIR)/EraseManager.o \
		   $(BIN_CPP_DIR)/FileEraser.o \
		   $(BIN_CPP_DIR)/FileUtil.o \
		   $(BIN_CPP_DIR)/Logging.o

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TARGET = libjefl.so
	JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64/
	JNI_PATH = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
else
	TARGET = libjefl.dll
	JNI_PATH = -I"$(JAVA_HOME)\include" -I"$(JAVA_HOME)\include\win32"
endif

vpath %.class $(JAVA_DIR)

all : $(TARGET)

$(TARGET) : $(CXX_OBJS)
	$(CXX) $(CXXFLAGS) -W -shared -o $(BIN_CPP_DIR)/$@ $+ $(CXX_LIBS)

$(BIN_CPP_DIR)/Logging.o : $(CPP_DIR)/logging/Logging.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BIN_CPP_DIR)/FileUtil.o : $(CPP_DIR)/fs/FileUtil.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BIN_CPP_DIR)/FileEraser.o : $(CPP_DIR)/fs/FileEraser.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BIN_CPP_DIR)/EraseManager.o : $(CPP_DIR)/fs/EraseManager.cpp
	$(CXX) $(CXXFLAGS) -fPIC $(JNI_PATH) -c $< -o $@

$(BIN_CPP_DIR)/LoadLibrary.o : $(CPP_DIR)/LoadLibrary.cpp
	$(CXX) $(CXXFLAGS) -fPIC $(JNI_PATH) -shared -c $< -o $@ $(CXX_LIBS)

clean :
	rm -f $(CXX_OBJS) $(TARGET)