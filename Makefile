build:
	mkdir build
	cd build && CXX=/usr/local/bin/clang++ cmake .. && make

test:
	mkdir build
	cd build && CXX=/usr/local/bin/clang++ cmake .. && make
	bash -c build/tests/triv_stl_test_bin

clean:
	rm -rf build
