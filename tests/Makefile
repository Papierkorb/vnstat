CC = gcc
CFLAGS = -Wall -Wextra -g -I../src
LDLIBS = -lm -lcheck
OBJS = vnstat_tests.o common_tests.o database_tests.o config_tests.o ifinfo_tests.o common.o ifinfo.o dbaccess.o dbcache.o cfg.o misc.o
VPATH = ../src

default: runtests

runtests: vnstat_tests
	./vnstat_tests

profile: CFLAGS += -fprofile-arcs -ftest-coverage
profile: LDLIBS += -fprofile-arcs -ftest-coverage
profile: runtests
	lcov -c -d $(PWD) -o coverage.lcov
	genhtml coverage.lcov --num-spaces 4 -o coverage

vnstat_tests: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o vnstat_tests

vnstat_tests.o: vnstat_tests.c vnstat_tests.h common_tests.h database_tests.h
common_tests.o: common_tests.c common_tests.h vnstat_tests.h common.h dbaccess.h cfg.h
database_tests.o: database_tests.c database_tests.h vnstat_tests.h dbaccess.h dbcache.h
config_tests.o: config_tests.c config_tests.h vnstat_tests.h common.h cfg.h
ifinfo_tests.o: ifinfo_tests.c ifinfo_tests.h vnstat_tests.h common.h ifinfo.h

common.o: common.c common.h
ifinfo.o: ifinfo.c ifinfo.h common.h dbaccess.h misc.h cfg.h
dbaccess.o: dbaccess.c dbaccess.h common.h
dbcache.o: dbcache.c dbcache.h dbaccess.h common.h ifinfo.h
cfg.o: cfg.c cfg.h common.h
misc.o: misc.c misc.h common.h

clean:
	rm -fr *.o *~ core *.i *.gc* test.log test.xml *.lcov coverage vnstat_tests