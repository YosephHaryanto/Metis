/****
* Image.h Class image used on Secret Sharing Manager class
*
* Copyright (c) Yoseph Haryanto.
****/

#pragma once

#include <vector>
#include <collection.h>

namespace MetisDll 
{
	public ref class Image sealed
	{
	public:
		Image();
		Image(int width, int height);
		Image(Windows::Foundation::Collections::IVector<int>^ in, int width, int height);

		/// <summary>
		/// Gets the height of the image.
		/// </summary>
		/// <returns>Image height</returns>
		int getHeight()	{ return _height; }
		
		/// <summary>
		/// Gets the width of the image.
		/// </summary>
		/// <returns>Image width</returns>
		int getWidth()	{ return _width; }
		
		/// <summary>
		/// Gets the n value of the shadow.
		/// </summary>
		/// <returns>n</returns>
		int getN(){ return _N; }

		/// <summary>
		/// Sets the image height.
		/// </summary>
		/// <param name="value">The value of height.</param>
		void setHeight(int value) { _height = value; }

		/// <summary>
		/// Sets the image width.
		/// </summary>
		/// <param name="value">The valueof width.</param>
		void setWidth(int value) { _width = value; }

		/// <summary>
		/// Sets the n value of the shadow.
		/// </summary>
		/// <param name="N">n</param>
		void setN(int N) { _N = N; }

		/// <summary>
		/// Modifies the value of pixel positioned in x and y.
		/// </summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <param name="value">The pixel value.</param>
		void ModifyPixel(int x, int y, int value){ _imageData->SetAt(y*getWidth() + x, value); }

		/// <summary>
		/// Gets the value of pixel positioned in x and y.
		/// </summary>
		/// <param name="x">x</param>
		/// <param name="y">y</param>
		/// <returns>Value of pixel</returns>
		int getPixel(int x, int y) { return _imageData->GetAt(y*getWidth() + x); }

		/// <summary>
		/// Inserts the pixel at last index of pixel.
		/// </summary>
		/// <param name="value">The pixel value.</param>
		void InsertPixel(int value){ _imageData->Append(value); }

		/// <summary>
		/// Gets the raw image data.
		/// </summary>
		/// <returns>Collection of pixel (Vector) </returns>
		Windows::Foundation::Collections::IVector<int>^ getImageData(){ return _imageData; }
	
	private:
		~Image();

		/// <summary>
		/// The raw image data
		/// </summary>
		Windows::Foundation::Collections::IVector<int>^ _imageData;
		
		/// <summary>
		/// The image height
		/// </summary>
		int _height;

		/// <summary>
		/// The image width
		/// </summary>
		int _width;

		/// <summary>
		/// The n value of shadow corresponding to f(n) in polynomial reconstruction
		/// </summary>
		int _N;
	};
}

