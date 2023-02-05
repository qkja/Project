cc=g++
parser:parser.cc 
	$(cc) -std=c++11 -o $@ $^ -lboost_system -lboost_filesystem 

.PHONY:clean
clean:
	rm -f parser
