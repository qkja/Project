cc=g++
PARSER=parser
SSVR=search_server

.PHONY:all
all:$(PARSER) $(SSVR)

$(PARSER):parser.cc
	$(cc) -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem
$(SSVR):server.cc 
	$(cc) -o $@ $^ -std=c++11 -ljsoncpp

.PHONY:clean
clean:
	rm -f $(SSVR) $(PARSER)





















# cc=g++

# parser:parser.cc
# 	$(cc) -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem

# .PHONY:clean
# clean:
# 	rm -f parser
