all: ig

BUILD := build
OBJS := $(BUILD)/objs
SOURCE := src
CC := gcc
TARGET := $(OBJS)/ig.o $(OBJS)/ig_connection.o $(OBJS)/ig_http_parser.o $(OBJS)/ig_request.o $(OBJS)/ig_response.o

ig: $(TARGET)
	test -d $(BUILD) || mkdir -p $(BUILD)
	$(CC) $(wildcard $(OBJS)/*.o) -luv -lhttp_parser -o $(BUILD)/ig

$(OBJS)/%.o: $(SOURCE)/%.c
	test -d $(OBJS) || mkdir -p $(OBJS)
	$(CC) -g -c -o $@ $<

clean:
	rm -rf $(BUILD)
