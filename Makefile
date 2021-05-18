build:
	mkdir build
	cd build && cmake .. && make

test:
	rm -rf build
	mkdir build
	cd build && cmake .. && make
	bash -c build/tests/triv_stl_test_bin

clean:
	rm -rf build
