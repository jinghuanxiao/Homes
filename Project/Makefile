#���ñ�����
CC=arm-none-linux-gnueabi-g++

INCLUDE  = -I Common -I Log -I Adns -I Sqlite3/include
LIBVAR   = -lsqlite3  -lpthread -lm -ldl
LIBPATH  = -L Sqlite3/lib

SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
ROOT_DIR=$(shell pwd)
BIN=myapp
OBJS_DIR=debug/obj
BIN_DIR=debug/bin
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}
export CC BIN OBJS_DIR BIN_DIR ROOT_DIR 
all:$(SUBDIRS) $(CUR_OBJS) DEBUG
$(SUBDIRS):ECHO
	make -C $@
DEBUG:ECHO
	make -C debug
ECHO:
	@echo $(SUBDIRS)
$(CUR_OBJS):%.o:%.cpp
	$(CC) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@  $(INCLUDE) $(LIBVAR) $(LIBPATH)
CLEAN:
	@rm $(OBJS_DIR)/*.o
	@rm -rf $(BIN_DIR)/*
