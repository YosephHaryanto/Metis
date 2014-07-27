#include "pch.h"
#include "Wavelet.h"

using namespace std;

Wavelet::Wavelet(int size, int iterations, int fractionalBits)
{
	/*
	if (size <= 0) throw new IllegalArgumentException("size not strictly positive");
	if (size != Integer.highestOneBit(size)) throw new IllegalArgumentException("size not a power of two");
	if (size > 4096) throw new IllegalArgumentException("size too large to support int size arithmetic");
	*/

	this->size = size;
	this->sizeSqr = size * size;

	setIterations(iterations);
	setFractionalBits(fractionalBits);
}

void Wavelet::setIterations(int iterations) {
	// if (iterations < 0) iterations = Integer.numberOfTrailingZeros(size);
	// if (1 << iterations > size) throw new IllegalArgumentException("too many iterations for size");
	this->iterations = iterations;
}

void Wavelet::setFractionalBits(int fractionalBits) {
	// if (fractionalBits < 0) fractionalBits = iterations << 1;
	// if (fractionalBits > 23) throw new IllegalArgumentException("fractionalBits exceeds 23, the largest storable in an int");
	this->fractionalBits = fractionalBits;
}

vector<int> Wavelet::filter(vector<int> values, vector<int> filter) {
	/*
	//validate arguments
	if (values == null) throw new IllegalArgumentException("null values");
	if (values.length != sizeSqr) throw new IllegalArgumentException("values array incorrect length");
	if (filter == null) {
		filter = new int[sizeSqr];
	}
	else {
		if (filter.length != sizeSqr) throw new IllegalArgumentException("filter array incorrect length");
	}
	*/

	//lazily allocate a buffer
	if (buffer.size == 0) 
		buffer = vector<int>(sizeSqr);

	//filter the values
	for (int i = 0; i < iterations; i++) {
		vector<int> s;
		vector<int> t;

		int length = size >> i;
		//horizontal processing
		s = filter;
		t = buffer;
		int hOffset = length >> 1;
		for (int y = 0; y < length; y++) {
			int sIndex, tIndex;
			tIndex = sIndex = y * size;
			for (int x = 0; x < length; x += 2) {
				int a = s[sIndex];
				int b = s[sIndex + 1];
				t[tIndex] = a + b;
				t[tIndex + hOffset] = a - b;
				sIndex += 2;
				tIndex++;
			}
		}
		//vertical processing
		s = buffer;
		t = filter;
		int vOffset = (length >> 1) * size;
		for (int x = 0; x < length; x++) {
			int sIndex, tIndex;
			sIndex = tIndex = x;
			for (int y = 0; y < length; y += 2) {
				int a = s[sIndex];
				int b = s[sIndex + size];
				t[tIndex] = a + b;
				t[tIndex + vOffset] = a - b;
				sIndex += size << 1;
				tIndex += size;
			}
		}

		length <<= 1;
	}

	//normalize the number of fractional bits before returning
	normalize(filter);
	return filter;
}

/**
* Converts a filter created by this object back into the supplied byte
* array. If no byte array is supplied a new one is created.
*
* If the <code>iterations</code> and <code>fractionalBits</code> parameters
* of this object have been modified since the filter was created then the
* data will not be faithfully reconstructed. If the number of fractional
* bits is less than its default value then the inversion may be imperfect
* due to accumulated rounding errors.
*
* <strong>This method destroys the supplied filter array - this is done
* intentionally for performance reasons. If you want to preserve your
* filter clone it before passing it into this method.</strong>
*
* @param filter an array containing the filter values, not null
* @param values an array which is to contain the recovered data, or null
* @return the array which contains the recovered data
*/

/*
* NOTE: As indicated, this implementation has not been thoroughly tested.
* In particular, it might be possible that this method could overflow when
* inverting large filters. I have not yet had the time to prove otherwise.
*/

vector<int> Wavelet::invert(vector<int> filter, vector<int> values) 
{
	//validate arguments
	/*if (filter == null) throw new IllegalArgumentException("null filter");
	if (filter.length != sizeSqr) throw new IllegalArgumentException("filter array incorrect length");
	if (values == null) {
		values = new byte[sizeSqr];
	}
	else {
		if (values.length != sizeSqr) throw new IllegalArgumentException("values array incorrect length");
	}*/

	//lazily allocate a buffer
	if (buffer.size == 0)
		buffer = vector<int>(sizeSqr);

	//reverse the filtering process
	for (int i = iterations - 1; i >= 0; i--) {
		vector<int> s;
		vector<int> t;

		int length = size >> i;
		//vertical processing
		s = filter;
		t = buffer;
		int vOffset = (length >> 1) * size;
		for (int x = 0; x < length; x++) {
			int sIndex, tIndex;
			sIndex = tIndex = x;
			for (int y = 0; y < length; y += 2) {
				int a = s[sIndex];
				int b = s[sIndex + vOffset];
				t[tIndex] = a + b;
				t[tIndex + size] = a - b;
				sIndex += size;
				tIndex += size << 1;
			}
		}
		//horizontal processing
		s = buffer;
		t = filter;
		int hOffset = length >> 1;
		for (int y = 0; y < length; y++) {
			int sIndex, tIndex;
			tIndex = sIndex = y * size;
			for (int x = 0; x < length; x += 2) {
				int a = s[sIndex];
				int b = s[sIndex + hOffset];
				t[tIndex] = a + b;
				t[tIndex + 1] = a - b;
				sIndex++;
				tIndex += 2;
			}
		}

		length >>= 1;
	}

	//remove the fractional bits and convert to bytes
	for (int i = 0; i < values.size; i++) {
		int value = filter[i] >> fractionalBits;
		if (value > 255) value = 255;
		else if (value < 0) value = 0;
		values[i] = value;
	}

	return values;
}

void Wavelet::normalize(vector<int> filter) 
{
	int shiftD = -2;
	int shiftY = (iterations << 1) - fractionalBits;

	int nextY = size >> (iterations - 1);
	for (int y = 0; y < size; y++) 
	{
		if (y == nextY) 
		{
			shiftY += shiftD;
			nextY <<= 1;
		}
		int i = y * size;
		int nextX = nextY;
		int shiftX = shiftY;
		for (int x = 0; x < size; x++) 
		{
			if (x == nextX) 
			{
				shiftX += shiftD;
				nextX <<= 1;
			}
			if (shiftX > 0)
			{
				filter[i] >>= shiftX;
			}
			else if (shiftX < 0) 
			{
				filter[i] <<= -shiftX;
			}
			i++;
		}
	}
}