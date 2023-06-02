SRCS_DIR := ./src
BUILD_DIR := ./build

SRCS := $(shell find $(SRCS_DIR) -name "*.cpp")
OBJS := $(subst $(SRCS_DIR),$(BUILD_DIR),$(SRCS))
OBJS := $(OBJS:.cpp=.o)

app.out: $(OBJS)
	g++ $(OBJS) -o $@

build/%.o : src/%.cpp
	g++ -c $< -o $@

clean:
	rm -f app.out
	rm -f build/*
