cc=g++
PARSER=parser

HTTP_SERVER=http_server 

.PHONY:all
all:$(PARSER) $(HTTP_SERVER)

$(HTTP_SERVER):http_server.cc
	$(cc) -o $@ $^ -std=c++11 -lpthread -lboost_system -lboost_filesystem -ljsoncpp

$(PARSER):parser.cc
	$(cc) -o $@ $^ -std=c++11 -lboost_system -lboost_filesystem

.PHONY:clean
clean:
	rm -f $(PARSER) $(HTTP_SERVER)

