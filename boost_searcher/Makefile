cc=g++
PARSER=parser
DUG=debug
HTTP_SERVER=http_server 
.PHONY:all
all:$(PARSER) $(DUG) $(HTTP_SERVER)

$(DUG):debug.cc
	$(cc) -o $@ $^ -std=c++11  -lboost_system -lboost_filesystem -ljsoncpp

$(PARSER):parser.cc
	$(cc) -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem

$(HTTP_SERVER):http_server.cc
	$(cc) -o $@ $^ -std=c++11 -lpthread -lboost_system -lboost_filesystem -ljsoncpp

.PHONY:clean
clean:
	rm -f $(PARSER) $(DUG) $(HTTP_SERVER)
