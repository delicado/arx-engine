TARGET = arx
CC = g++
OBJS= arx_syscore.o arx_system.o arx_test.o arx_component.o\
	arx_sysmgr.o
LIBS= -L./depends/lua-5.2.2 -llua
r: run

arx_system.o: arx_system.cpp arx_system.h
arx_syscore.o: arx_syscore.cpp arx_sysmgr.cpp arx_system.cpp arx_syscore.h arx_sysmgr.h arx_system.h
arx_test.o: arx_test.cpp
arx_component.o: arx_component.cpp arx_system.cpp arx_component.h arx_system.h arx_containers.h \
	arx_declares.h 
arx_sysmgr.o : arx_sysmgr.cpp arx_system.cpp arx_sysmgr.h arx_containers.h arx_system.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) 

clean:
	rm $(OBJS) $(TARGET)

run: $(TARGET)
	run_ca $(TARGET)