.PHONY: clean build test run

clean:
	@rm -rf build/*
	@rmdir build

build: build/raytracer

build/raytracer: src/main.cpp src/camera.cpp src/sphere.cpp src/*.h
	@mkdir -p build
	g++ src/main.cpp src/camera.cpp src/sphere.cpp -I src -o build/raytracer

test: build/tests
	./build/tests

build/tests: test/*.cpp
	@mkdir -p build
	g++ test/*.cpp -I src -o build/tests

run : build
	@rm -rf out
	@mkdir -p out
	./build/raytracer > out/output.ppm