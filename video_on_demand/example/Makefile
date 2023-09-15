mytest:mysql_test.cc
	g++ -o $@ $^  -std=c++11 -L/usr/lib64/mysql -lmysqlclient  # 编译时用-L指明所在目录
.PHONY:clean
	rm -rf mytest	
