OSFLAG :=
ifeq ($(OS), Windows_NT)
	executable = tests.exe
else
	executable = ./tests
endif

.PHONY: test-compile test test-all example-compile

test-compile:
ifeq (,$(wildcard ./tests/tests-main.o))
	$(info Compiling tests-main.cpp, this only needs to be done once.)
	@g++ ./tests/tests-main.cpp -c -o ./tests/tests-main.o
	@g++ -std=c++17 ./tests/tests-main.o ./tests/tests-gol.cpp -o ./tests/tests
else
	@g++ -std=c++17 ./tests/tests-main.o ./tests/tests-gol.cpp -o ./tests/tests
endif
test:
	@./tests/$(executable)
test-all: test-compile test

example-compile:
	@g++ ./example/blinker_oscillator.cpp         -o ./example/blinker_oscillator
	@g++ ./example/toad_oscillator.cpp            -o ./example/toad_oscillator
	@g++ ./example/beacon_oscillator.cpp          -o ./example/beacon_oscillator
	@g++ ./example/pulsar_oscillator.cpp          -o ./example/pulsar_oscillator
	@g++ ./example/pentadecathlon_oscillator.cpp  -o ./example/pentadecathlon_oscillator
	@g++ ./example/60P312_oscillator.cpp          -o ./example/60P312_oscillator
	
	@g++ ./example/randomized_board.cpp           -o ./example/randomized_board