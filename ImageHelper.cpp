#include "pch.h"
#include "ImageHelper.h"

using namespace std;
using namespace MetisDll;
using namespace Platform::Collections;

/// <summary>
/// Converting collection value of Red, Green, and Blue into collection of pixel
/// </summary>
/// <param name="R">The collection of red value.</param>
/// <param name="G">The collection of green value.</param>
/// <param name="B">The collection of blue value.</param>
/// <returns>Colletion of pixel in integer</returns>
Vector<int>^ ImageHelper::RGBtoint(Vector<int>^ R, Vector<int>^ G, Vector<int>^ B)
{
	Vector<int>^ result = ref new Vector<int>(); 

	for (int i =0; i < R->Size ;i++)
	{
		result->Append(((R->GetAt(i) & 0x0ff) << 16) | ((G->GetAt(i) & 0x0ff) << 8) | (B->GetAt(i) & 0x0ff));
	}
	return result;
}

/// <summary>
/// Convert pixel value in form of integer into separate value
/// </summary>
/// <param name="pixel">The pixel value.</param>
/// <returns>Value of red, green, and blue in Vector</returns>
Vector<int>^ ImageHelper::intToRGB(int pixel)
{
	Vector<int>^ result =  ref new Vector<int>();
	result->Append (pixel >> 16 & 0xFF);
	result->Append (pixel >> 8 & 0xFF);
	result->Append (pixel & 0xFF);
	return result;
}

