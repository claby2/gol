OSFLAG :=
ifeq ($(OS), Windows_NT)
	executable = test.exe
else
	executable = ./test
endif

test-compile:
	@g++ -std=c++17 ./tests/test.cpp -o ./tests/test
test:
	@./tests/$(executable)
test-all: test-compile test

example-compile:
	@g++ ./example/blinker_oscillator.cpp -o ./example/blinker_oscillator
	@g++ ./example/toad_oscillator.cpp    -o ./example/toad_oscillator
	@g++ ./example/beacon_oscillator.cpp  -o ./example/beacon_oscillator

	@g++ ./example/randomized_board.cpp   -o ./example/randomized_board