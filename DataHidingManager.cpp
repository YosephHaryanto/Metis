#include "pch.h"
#include "DataHidingManager.h"
#include <cmath>
#include <vector>

using namespace Metis;
using namespace std;

DataHidingManager::DataHidingManager()
{
	// some constant for DCT equaition
	this->SQRT2o2 = 1.414213562373095048801688724209 * 0.5;
	const double inv16 = 1.0 / 16.0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
//			this->cosine[j][i] = cos(M_PI* j * (2.0 * i + 1) * inv16);
		}
	}
}

// the COMPLEX DCT equation, lol
vector<double> DataHidingManager::DCT(vector<int> B)
{
	vector<double> A = vector<double>(8);
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			A[y * 8 + x] = 0;
			for (int u = 0; u < 8; u++)
				for (int v = 0; v < 8; v++)
					A[y * 8 + x] += alpha(u) * alpha(v) * B[v*8 + u] *cosine[u][x] * cosine[v][y];
		}
	}
	return A;
}

vector<int> DataHidingManager::SecretImageDifferencing(Image SecretImage)
{
	vector<int> result = vector<int>(SecretImage.getHeight() * SecretImage.getWidth());

	//on the beginning, we use the difference between 128 and teh first pixel for convenience
	result[0] = abs(128 - SecretImage.getPixel(0, 0));

	
	int xNow = 1, yNow = 0;
	int prevPixel = SecretImage.getPixel(0, 0);

	//counting the difference of ajactent pixel
	while (yNow< SecretImage.getHeight())
	{
		result[SecretImage.getWidth()* yNow + xNow] = SecretImage.getPixel(xNow, yNow) - prevPixel;
		// make zig zag move 
		xNow = yNow % 2 == 0?  xNow++:xNow--;
		if (xNow == SecretImage.getWidth())
		{
			yNow++; xNow += SecretImage.getWidth() - 1;
		}
		else if ( xNow == -1)
		{
			yNow++; xNow = 0;
		}
	}
	return result;
}

vector<int> DataHidingManager::CoverImageDifferencing(Image CoverImage)
{
	vector<int> result = vector<int>(CoverImage.getHeight() * CoverImage.getWidth());

	//on the beginning, we use the difference between 128 and teh first pixel for convenience
	result[0] = abs(128 - CoverImage.getPixel(0, 0));


	int xNow = 1, yNow = 0;
	int prevPixel = CoverImage.getPixel(0, 0);

	//counting the difference of ajactent pixel
	while (yNow< CoverImage.getHeight())
	{
		result[CoverImage.getWidth()* yNow + xNow] = CoverImage.getPixel(xNow, yNow) - prevPixel;
		// make zig zag move 
		xNow = yNow % 2 == 0 ? xNow++ : xNow--;
		if (xNow == CoverImage.getWidth())
		{
			yNow++; xNow += CoverImage.getWidth() - 1;
		}
		else if (xNow == -1)
		{
			yNow++; xNow = 0;
		}
	}
	return result;
}
