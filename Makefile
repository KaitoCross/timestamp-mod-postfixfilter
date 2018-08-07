all: dmail-filter


dmail-filter:
	g++ main.cpp -o $@ -std=c++11

clean:
	rm -rf dmail-filter
