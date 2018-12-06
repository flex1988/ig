all: ig

BUILD := build
OBJS := $(BUILD)/objs
SOURCE := src
CC := gcc
TARGET := $(OBJS)/ig.o $(OBJS)/ig_connection.o $(OBJS)/ig_http_parser.o $(OBJS)/ig_request.o $(OBJS)/ig_response.o
SRC := $(SOURCE)/ig.c $(SOURCE)/ig_connection.c $(SOURCE)/ig_http_parser.c $(SOURCE)/ig_request.c $(SOURCE)/ig_response.c

ig: $(TARGET)
	test -d $(BUILD) || mkdir -p $(BUILD)
	$(CC) $(wildcard $(OBJS)/*.o) -luv -lhttp_parser -o $(BUILD)/ig

so: $(TARGET)
	test -d $(BUILD) || mkdir -p $(BUILD)
	$(CC) $(wildcard $(SOURCE)/*.c) -luv -lhttp_parser -lpthread -D_GNU_SOURCE -fPIC -shared -std=c99 -o $(BUILD)/ig.so

run: so
	scheme --script scheme/server.sc

$(OBJS)/%.o: $(SOURCE)/%.c
	test -d $(OBJS) || mkdir -p $(OBJS)
	$(CC) -g -c -o $@ $<

clean:
	rm -rf $(BUILD)
