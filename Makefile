build:
	g++ --pedantic -Wall diffraction.cpp

clean:
	rm ./a.out
	rm ./intensity.data
run:
	./a.out