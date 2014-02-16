#pragma once

#include <vector>

ref class Wavelet sealed
{
public:

	/**
	* Constructs a new object for performing filtering. Individual filtering
	* instances are constructed to operate on data of a predetermined size. All
	* arrays passed to a filter must have a length which corresponds to the
	* size specified at construction (specifically size x size).
	*
	* @param size the length of the side of all squares of data/filter values
	*/
	Wavelet(int size){ Wavelet(size, -1, -1); };

	/**
	* Constructs a new object for performing filtering. Individual filtering
	* instances are constructed to operate on data of a predetermined size. All
	* arrays passed to a filter must have a length which corresponds to the
	* size specified at construction (specifically size x size). See
	*
	* @see #setIterations(int) for information about the iterations parameter
	* @see #setFractionalBits(int) for information about the fractionalBits parameter
	*
	* @param size the length of the side of all squares of data/filter values
	* @param iterations the number of iterations performed during filtering, or
	*        -1 to use the default value
	* @param fractionalBits the number of binary fractional bits in the
	* 	      number representation used in filters, or -1 to use the default
	*        value
	*/
	Wavelet(int size, int iterations, int fractionalBits);

	/**
	* The number of iterations that will be applied during a call to the
	* <code>filter</code> method.
	*
	* @see #setIterations(int) for more information
	*
	* @return the number of iterations performed during filtering, never negative
	*/
	int getIterations() {return iterations;}

	/**
	 Specifies the number of times that the Haar wavelet is successively
	 applied during a call to the <code>filter</code> method. This cannot
	 exceed ln2(size). This maximum forms the sensible default value and
	 can be specified by passing a negative number to this method.
	
	 @param the number of iterations performed during filtering, or -1 for the
	        default value
	*/
	
	void setIterations(int iterations);

	
	///<summary>
	/// Specifies the number of bits in the integers returned by the
	/// <code>filter</code> method that represent fractions of a whole number.
	/// If fractionalBits is not zero, these bits will form the least
	/// significant bits of the integers. Due to the size constraints that arise
	/// from arithmetic on <code>int</code>s the number of fractional bits cannot
	/// exceed 23. The sensible default value for the number of fractional bits
	/// is twice the number of iterations; this default can be specified by
	/// passing a negative number to this method.
	///</summary>
	/// @param fractionalBits the number of binary fractional bits in the number
	///        representation used in filters, or -1 for the default value
	void setFractionalBits(int fractionalBits);

	/**
	
	* Filters the byte values supplied by applying the Haar wavelet for a
	* number of iterations and stores the result in the specified integer array.
	* If no filter array is supplied then a new array is created. The values
	* returned may have been scaled to accomodate fractional bits.
	*
	* @param values a byte array of length containing the values to be filtered, not null
	* @param filter an array which is to contain the filter values, or null
	* @return the array which contains the filter values
	*/
	std::vector<int> filter(std::vector<int> values, std::vector<int> filter);

	/*
	* Adjusts for accumulated fractional bits in the raw filter array.
	*/
	void normalize(std::vector<int> filter);

	std::vector<int> invert(std::vector<int> filter, std::vector<int> values);

private:
	/**
	The length of the side of the data to be filtered
	*/
	int size;

	/**
	The square of the size.
	*/
	int sizeSqr;

	/**
	A buffer that is allocated for performing filtering.
	*/
	std::vector<int> buffer;

	/**
	The number of filtering iterations performed.
	*/
	int iterations;

	/**
	The number of bits in the filter arrays processed.
	*/
	int fractionalBits;

};

