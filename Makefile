CXXFLAGS = -std=c++14
LDLIBS = -lboost_program_options

christmas_tree: christmas_tree.cpp

.PHONY: run clean

run: christmas_tree
	./christmas_tree

clean:
	$(RM) christmas_tree *.o
