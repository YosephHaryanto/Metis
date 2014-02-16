#include "pch.h"
#include "Image.h"
#include <algorithm>

using namespace MetisDll;
using namespace std;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;

Image::Image()
{
	_imageData = ref new Vector<int>();
}

Image::Image(IVector<int>^ in, int width, int height)
{
	_imageData = in;
	_width = width;
	_height = height;
}

Image::~Image()
{
	delete(_imageData);
}

Image::Image(int width, int height)
{
	_imageData = ref new Vector<int>(width*height);
	_width = width;
	_height = height;
}
