build:
	mkdir build
	cd build && cmake .. && make

test:
	mkdir build
	cd build && cmake .. && make
	bash -c build/tests/triv_stl_test_bin

clean:
	rm -rf build
