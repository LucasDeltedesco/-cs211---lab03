build:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp

commit:
	git add.
	git commit -m "committed changes"