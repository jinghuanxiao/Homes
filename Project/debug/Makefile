OBJS=*.o
ODIR=obj
$(ROOT_DIR)/$(BIN_DIR)/$(BIN):$(ODIR)/$(OBJS)
	$(CC) -o $@ $^   -I $(ROOT_DIR)/Sqlite3/include -L $(ROOT_DIR)/Sqlite3/lib -lsqlite3  -lpthread -lm -ldl
