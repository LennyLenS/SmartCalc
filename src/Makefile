CC	=	gcc 
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
SOURCES = polish.c
OBJECTS = $(SOURCES:.c=.o)
TESTEXEC = tests/test
BUILD_DIR = build
ALL_PROJECT = *.c *.h Calc/*.cpp Calc/*.h tests/*.c tests/*.h
EXEC = /build/Smart_Calc.app/


LIBS_ADDITIONAL = 
ifeq ($(OS), Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

ifeq ($(OS), Linux)
	LIBS_ADDITIONAL = -lm -lsubunit
	EXEC = /build/SmartCalc
endif


all: install open

.c.o:
	$(CC) $(CFLAGS) $< -o $@

install:
		[ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)
		cd build && qmake ../Calc
		make -C ./build/

open:
ifeq ($(shell uname), Linux)
	.$(EXEC)
else
	open .$(EXEC)
endif

uninstall: clean
		rm -Rf build/
		rm -rf SmartCalc.tar

clean:
		rm -rf tests/*.html tests/*.css
		rm -f $(TESTEXEC) ../SmartCalc.tar .gitkeep .DS_Store qt_project/.qmake.stash
		find . -name '*.gcno' -type f -delete
		find . -name '*.gcda' -type f -delete
		find . -name '*.gcov' -type f -delete
		rm -rf *.o .qmake.stash .clang-format
		rm -rf qt_project/.qtc_clangd/
		rm -rf qt_project/.clang-format
		rm -rf report

dvi:
		open README.md

dist: uninstall clean
	cd ../ && tar -cf SmartCalc.tar src

test: 
	find . -name '*.gcda' -type f -delete
	$(CC) $(CFLAGS) -c tests/test.c
	$(CC) $(CFLAGS) test.o test_main.c --coverage $(SOURCES) -o $(TESTEXEC) -lcheck $(LIBS_ADDITIONAL)
	./$(TESTEXEC)
	gcov c_calc_polish.gcda

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	find . -name '*.gcno' -type f -delete
	find . -name '*.gcda' -type f -delete

lint: test
	clang-format -n -style=google $(ALL_PROJECT)

make_style:
	clang-format -i -style=google $(ALL_PROJECT)
