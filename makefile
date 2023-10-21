.PHONY:clean a.out
a.out:main.cc
	g++ $^ -o $@ -std=c++17 -O3
clean:
	rm -rf a.out