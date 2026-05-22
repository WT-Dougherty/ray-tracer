build: build/raytracer

build/raytracer: src/main.cpp src/camera.cpp src/sphere.cpp src/*.h
	@mkdir -p build
	g++ src/main.cpp src/camera.cpp src/sphere.cpp -I src -o build/raytracer

clean:
	@rm -rf build/*
	@rmdir build

run : build
	@rm -rf out
	@mkdir -p out
	./build/raytracer > out/output.ppm