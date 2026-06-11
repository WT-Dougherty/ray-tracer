.PHONY: clean build test run

TEST_DEPS = src/sphere.cpp src/camera.cpp

clean:
	@rm -rf build/*
	@rmdir build

build: build/raytracer

build/raytracer: src/*.cpp src/*.h src/util/*.h
	@mkdir -p build
	g++ src/*.cpp -I src -O3 -march=native -std=c++17 -o build/raytracer

test: build/tests
	./build/tests

build/tests: test/*.cpp $(TEST_DEPS)
	@mkdir -p build
	g++ test/*.cpp $(TEST_DEPS) -I src -std=c++17 -o build/tests

run : build
	@rm -rf out
	@mkdir -p out
	./build/raytracer > out/output.ppm