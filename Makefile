CXX = gcc
src = $(wildcard src/*.c examples/*.c)
obj = $(src:.c=.o)

LDFLAGS = -std=c99 -O2

onetimepad: $(obj)
	@mkdir -p bin
	$(CXX) -o bin/$@ $^ $(LDFLAGS)

clean:
	rm $(obj)
