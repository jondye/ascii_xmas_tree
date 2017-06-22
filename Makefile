CXXFLAGS = -std=c++14

christmas_tree: christmas_tree.cpp

.PHONY: run clean

run: christmas_tree
	./christmas_tree

clean:
	$(RM) christmas_tree *.o
