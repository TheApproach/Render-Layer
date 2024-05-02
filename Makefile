build:
	@g++ -o ./bin/render server.cpp -std=c++20
run: build
	@./bin/render
clean:
	@rm -rf ./bin/render
	@echo "Cleaned up the build files"
client_build:
	@g++ -o ./bin/client client.cpp -std=c++20
client_run: client_build
	@./bin/client
test_build:
	@g++ -o ./bin/test test.cpp -std=c++20
test_run: test_build
	@./bin/test
