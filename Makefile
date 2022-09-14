# CSCI 2021 Project 4 Makefile
AN = p4
CLASS = 2021

CFLAGS = -Wall -Werror -g -Og
# CFLAGS = -Wall -g -O3
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	matata_print \
	matata_benchmark \
	search_benchmark \

all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o vgcore.* 

help :
	@echo 'Typical usage is:'
	@echo '  > make                          # build all programs'
	@echo '  > make clean                    # remove all compiled items'
	@echo '  > make zip                      # create a zip file for submission'
	@echo '  > make prob1                    # built targets associated with problem 1'
	@echo '  > make prob1 testnum=5          # run problem 1 test #5 only'
	@echo '  > make test-prob2               # run test for problem 2'
	@echo '  > make test                     # run all tests'

############################################################
# 'make zip' to create p2-code.zip for submission
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi

# build .o files from corresponding .c files
%.o : %.c
	$(CC) -c $<

# Matrix A^T*A optimization problem
matata_print : matata_print.o matvec_util.o matata_base.o matata_optm.o
	$(CC) -o $@ $^

matata_benchmark : matata_benchmark.o matvec_util.o matata_base.o matata_optm.o
	$(CC) -o $@ $^ -lm


# Search Algorithm Problem
search_benchmark : search_benchmark.o search_funcs.o
	$(CC) -o $@ $^

# Testing Targets
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

################################################################################
# Testing Targets
test: test-prob1 test-prob2

test-setup :
	@chmod u+rx testy

test-prob1: matata_benchmark matata_print test-setup
	./testy test_matata.org $(testnum)

test-prob2: search_benchmark test-setup
	./testy test_search_benchmark.org $(testnum)

clean-tests :
	rm -rf test-results


