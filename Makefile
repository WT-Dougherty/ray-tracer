.PHONY: clean build test run

TEST_DEPS = src/sphere.cpp src/camera.cpp

clean:
	@rm -rf build/*
	@rmdir build

build: build/raytracer

build/raytracer: src/*.cpp src/*.h
	@mkdir -p build
	g++ src/*.cpp -I src -o build/raytracer

test: build/tests
	./build/tests

build/tests: test/*.cpp $(TEST_DEPS)
	@mkdir -p build
	g++ test/*.cpp $(TEST_DEPS) -I src -o build/tests

run : build
	@rm -rf out
	@mkdir -p out
	./build/raytracer > out/output.ppm