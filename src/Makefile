CFLAGS=-Wall -Wextra -Werror -std=c11
TEST_FLAGS=-lcheck -lm -lpthread

C_FILES=ch_stack.c db_stack.c notation.c count.c credit.c check_func.c test.c
CPP_FILES=./gui/main.cpp ./gui/qcustomplot.cpp ./gui/SmartCalc.cpp
H_FILES=ch_stack.h db_stack.h notation.h count.h credit.h check_func.h
H_FILES+=./gui/qcustomplot.h ./gui/SmartCalc.h
GUI_FILES=./gui/gui.pro ./gui/Makefile
O_FILES=ch_stack.o db_stack.o notation.o count.o credit.o check_func.o test.o

ifeq ($(shell uname -s), Linux)
    TEST_FLAGS +=-lsubunit
endif

all: build

build: install gcov_report
	./gui/gui

install: $(H_FILES) $(C_FILES) $(CPP_FILES)
	$(MAKE) -C gui

uninstall:
	rm -rf ./gui/moc_predefs.h
	rm -rf ./gui/moc_qcustomplot.cpp
	rm -rf ./gui/.qmake.stash
	rm -rf ./gui/*.o
	rm -rf ./gui/gui

clean:
	rm -rf *.o *.html *.gcda *.gcno *.css *.out *.info report docs .clang-format

dvi: ./gui
	mkdir -p ./docs
	doxygen Doxyfile

dist: $(C_FILES) $(CPP_FILES) $(H_FILES) $(GUI_FILES) Makefile
	mkdir -p ./dist
	tar cvzf ./dist/SmartCalc_1.0.tgz $(C_FILES) $(CPP_FILES) $(H_FILES) $(GUI_FILES) Makefile

tests: $(O_FILES)
	gcc -o test.out $(O_FILES) $(TEST_FLAGS)
	./test.out

gcov_report: $(H_FILES) $(C_FILES)
	gcc $(CFLAGS) --coverage -o make_report.out $(C_FILES) $(TEST_FLAGS)
	./make_report.out
	lcov -t "make_report" -o make_report.info -c -d .
	genhtml -o report make_report.info
	open report/index.html

style: clean
	cppcheck *.h *.c
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h

test.o: test.c
	gcc $(CFLAGS) -c test.c

ch_stack.o: ch_stack.h ch_stack.c
	gcc $(CFLAGS) -c ch_stack.c

db_stack.o: db_stack.h db_stack.c
	gcc $(CFLAGS) -c db_stack.c

notation.o: notation.h notation.c
	gcc $(CFLAGS) -c notation.c

count.o: count.h count.c
	gcc $(CFLAGS) -c count.c

credit.o: credit.h credit.c
	gcc $(CFLAGS) -c credit.c

check_func.o: check_func.h check_func.c
	gcc $(CFLAGS) -c check_func.c
