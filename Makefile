TARGET = iso

SRCS  = $(shell find . -type f -name *.cpp)
HEADS = $(shell find . -type f -name '*.h')
OBJS = $(SRCS:.cpp=.o)
DEPS = Makefile.depend

INCLUDES = -I.
CXXFLAGS = $(INCLUDES) -std=c++17
LDFLAGS = -lm


all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)

run: all
	@./$(TARGET)

.PHONY: depend clean
depend:
	$(CXX) $(INCLUDES) -MM $(SRCS) > $(DEPS)
	@sed -i -E "s/^(.+?).o: ([^ ]+?)\1/\2\1.o: \2\1/g" $(DEPS)

clean:
	$(RM) $(OBJS) $(TARGET)

-include $(DEPS)