SRC_DIR = ../src
JNI_DIR = ../jni
CFLAGS = -g3 -std=c++17 -ggdb3 -O0 -Wno-literal-suffix

CPP_LIB = -lstdc++fs
SRC_MAIN = erase_fs.o
SRC_ERASE = erase_content.o

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TARGET = libjefl.so
	JNI_PATH = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
else
	TARGET = libjefl.dll
	JNI_PATH = -I"$(JAVA_HOME)\include" -I"$(JAVA_HOME)\include\win32"
endif

vpath %.class $(SRC_DIR)

all : $(TARGET)

$(TARGET) : $(SRC_MAIN) $(SRC_ERASE)
	g++ $(CFLAGS) -W -shared -o $@ $+ $(CPP_LIB)

erase_content.o : ../jni/erase/erase_content.cpp ../jni/erase/erase_content.hpp  
	g++ $(CFLAGS) -fPIC -c $< -o $@

erase_fs.o : ../jni/erase_fs.cpp erase_fs.hpp 
	g++ $(CFLAGS) -fPIC $(JNI_PATH) -shared -c $< -o $@ $(CPP_LIB)

erase_fs.hpp : ../bin/org/kl/erase/EraseFS.class
	javac -h $(JNI_DIR) ../src/org/kl/erase/EraseFS.java \
				../src/org/kl/state/OverwrideMode.java	\
				../src/org/kl/error/EraseException.java		

clean :
	rm -f erase_fs.o erase_content.o $(TARGET)