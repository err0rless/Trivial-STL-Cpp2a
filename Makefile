build:
	mkdir build -p
	cd build && cmake .. && make -j16

test: build
	bash -c build/tests/triv_stl_test_bin

clean:
	rm -rf build

.PHONY: build test clean
