OSFLAG :=
ifeq ($(OS), Windows_NT)
	executable = test.exe
else
	executable = ./test
endif

compile:
	@g++ -std=c++17 test.cpp -o test
test:
	@$(executable)
all: compile test