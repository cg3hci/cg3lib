/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
 */

#include <iostream>

#include <cg3/cg3lib.h>
#include <cg3/data_structures/arrays/arrays.h>

int main(int argc, char *argv[])
{
    CG3_SUPPRESS_WARNING(argc);
    CG3_SUPPRESS_WARNING(argv);

	std::cout << "------ Arrays sample ------" << std::endl << std::endl;

	srand(time(0));

	const unsigned int N = 5;

	cg3::Array<int, N> array5D; // defines a 5-dimensions array (sizes: 0x0x0x0x0)

	//positions of the elements are not preserved here (use conservativeResize for element preserving)
	array5D.resize(3, 4, 5, 6, 7); // changes the sizes of the array

	//cycle on all the elements of the array
	for (unsigned int i = 0; i < array5D.size(0); i++){
		for (unsigned int j = 0; j < array5D.size(1); ++j){
			for (unsigned int k = 0; k < array5D.size(2); ++k){
				for (unsigned int l = 0; l < array5D.size(3); ++l){
					for (unsigned int m = 0; m < array5D.size(4); ++m){
						array5D(i,j,k,l,m) = rand() % 10;
					}
				}
			}
		}
	}

	std::cout << "The element in position 1,1,1,1,1 is: " << array5D(1,1,1,1,1) << std::endl;

	//creates a 4D array starting from the second 4D array contained in array5D.
	cg3::Array4D<int> array4D(array5D.subArray(1));

	std::cout << "The element in position 1,1,1,1 is: " << array4D(1,1,1,1) << std::endl;

	//carray is a simple C array that contains the elements of array4D
	//in row-major representation, starting from the element in position (1, 1, 1, 0)
	const int* carray = array4D.cArray(1,1,1);

	std::cout << "Accessing carray[1]: " << carray[1] << std::endl;

	return 0;
}
