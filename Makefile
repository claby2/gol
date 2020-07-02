OSFLAG :=
ifeq ($(OS), Windows_NT)
	test-executable = tests.exe
else
	test-executable = ./tests
endif
ifeq ($(OS), Windows_NT)
	preview-executable = preview.exe
else
	preview-executable = ./preview
endif

.PHONY: test-compile test test-all example-compile preview-compile preview preview-all

test-compile:
ifeq (,$(wildcard ./tests/tests-main.o))
	$(info Compiling tests-main.cpp, this only needs to be done once.)
	@g++ ./tests/tests-main.cpp -c -o ./tests/tests-main.o
	@g++ -std=c++17 ./tests/tests-main.o ./tests/tests-gol.cpp -o ./tests/tests
else
	@g++ -std=c++17 ./tests/tests-main.o ./tests/tests-gol.cpp -o ./tests/tests
endif
test:
	@./tests/$(test-executable)
test-all: test-compile test

example-compile:
	@g++ ./example/blinker_oscillator.cpp         -o ./example/blinker_oscillator
	@g++ ./example/toad_oscillator.cpp            -o ./example/toad_oscillator
	@g++ ./example/beacon_oscillator.cpp          -o ./example/beacon_oscillator
	@g++ ./example/pulsar_oscillator.cpp          -o ./example/pulsar_oscillator
	@g++ ./example/pentadecathlon_oscillator.cpp  -o ./example/pentadecathlon_oscillator
	@g++ ./example/60P312_oscillator.cpp          -o ./example/60P312_oscillator
	
	@g++ ./example/randomized_board.cpp           -o ./example/randomized_board

	@g++ ./example/mazectric.cpp                  -o ./example/mazectric

preview-compile:
	@g++ ./preview/preview.cpp -lSDL2main -lSDL2  -o ./preview/preview
preview:
	@./preview/$(preview-executable)
preview-all: preview-compile preview-run