build:
	@g++ -std=c++20 -o ./bin/main ./approach/main.cpp
run: build
	@./bin/main