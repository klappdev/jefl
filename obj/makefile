CLASS_PATH = ../src
CFLAGS = -g3 -std=c++17 -lstdc++fs -ggdb3 -O0 -Wno-literal-suffix

SRC_MAIN = erase_fs.o

vpath %.class $(CLASS_PATH)

all : libjefl.so

libjefl.so : $(SRC_MAIN)
	g++ $(CFLAGS) -W -shared -o $@ $+ 

erase_fs.o : ../jni/erase_fs.cpp erase_fs.hpp 
	g++ $(CFLAGS) -fPIC -I/usr/lib/jvm/jdk-10.0.1/include \
	-I/usr/lib/jvm/jdk-10.0.1/include/linux -shared -c $< -o $@

erase_fs.hpp : ../bin/org/kl/erase/EraseFS.class
	javac -h ../jni ../src/org/kl/erase/EraseFS.java \
				../src/org/kl/state/OverwrideMode.java

clean :
	rm -f erase_fs.o libjefl.so