#pragma once
#include <collection.h>

namespace MetisDll 
{
	class ImageHelper
	{
	public:
		/// <summary>
		/// Converting the value of Red, Green, and Blue into pixel value
		/// </summary>
		/// <param name="R">The red value.</param>
		/// <param name="G">The green value.</param>
		/// <param name="B">The blue value.</param>
		/// <returns>The pixel value in integer </returns>
		static int RGBtoint(int R, int G, int B) { return ((R & 0x0ff) << 16) | ((G & 0x0ff) << 8) | (B & 0x0ff); }
		
		static Platform::Collections::Vector<int>^ RGBtoint
			(Platform::Collections::Vector<int>^ R, Platform::Collections::Vector<int>^ G, Platform::Collections::Vector<int>^ B);
		
		static Platform::Collections::Vector<int>^ intToRGB(int pixel);
	};
}

