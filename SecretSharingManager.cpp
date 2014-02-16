#include "pch.h"
#include "SecretSharingManager.h"
#include "Lagrange.h"
#include "ImageHelper.h"

#include <ppltasks.h>
#include <math.h>

using namespace MetisDll;
using namespace concurrency;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Platform::Collections;
using namespace std;


/// <summary>
/// Create the shadows asynchronously.
/// </summary>
/// <param name="imageData">The original image data that designed as the secret</param>
/// <param name="n">Number of shadow created</param>
/// <param name="r">Number of minimum shadow to reconstruct.</param>
/// <returns>
/// Task of Image list
/// </returns>
IAsyncOperationWithProgress<IVector<Image^>^, int >^ SecretSharingManager::CreateShadow(Image^ imageData, int n, int r)
{
	return create_async([this, imageData, n, r]
		(progress_reporter<int> reporter, cancellation_token cts) -> IVector<Image^>^ {

		//prepare variable for progress reporting
		double pConvert = 25;
		double pShadowing = 70;
		double pFinishing = 5;
		int progress = 0;

		int height = imageData->getHeight();
		int width = imageData->getWidth();

		//converting all the value above 250
		Vector<int>^ convertedImage =  ref new Vector<int>();
		
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Vector<int>^ pixel = ImageHelper::intToRGB(imageData->getPixel(j, i));

				if (pixel->GetAt(0) >= 250 || pixel->GetAt(1) >= 250 || pixel->GetAt(2) >= 250)
				{
					int Rd = pixel->GetAt(0) >= 250 ? 250 : pixel->GetAt(0);
					int Gd = pixel->GetAt(1) >= 250 ? 250 : pixel->GetAt(1);
					int Bd = pixel->GetAt(2) >= 250 ? 250 : pixel->GetAt(2);

					int Rr = pixel->GetAt(0) >= 250 ? pixel->GetAt(0) - 250 : 0;
					int Gr = pixel->GetAt(1) >= 250 ? pixel->GetAt(1) - 250 : 0;
					int Br = pixel->GetAt(2) >= 250 ? pixel->GetAt(2) - 250 : 0;

					convertedImage->Append(ImageHelper::RGBtoint(Rd, Gd, Bd));
					convertedImage->Append(ImageHelper::RGBtoint(Rr, Gr, Br));
				}
				else
					convertedImage->Append(imageData->getPixel(j, i));
				progress = (double)((i *width) + j ) /(double) (width*height) * pConvert;
				reporter.report(progress);
			}
		}
		
		//preparing the result shadows
		int numPixels = convertedImage->Size;
		Vector <Image^>^ shadows = ref new Vector<Image^>();
		int shadowHeight = ceil((double)numPixels / (double)n/(double)width);
		for (int i = 1; i <= n; i++)
		{
			shadows->Append(ref new Image());
			shadows->GetAt(i-1)->InsertPixel(ImageHelper::RGBtoint(n, r, i));
		}

		int curX = 1, curY = 0, curPixel = 0;

		// we interate until we take all the pixel
		while (curPixel < numPixels)
		{
			for (int i = 1; i <= n; i++)
			{
				int valueR = 0;
				int valueG = 0;
				int valueB = 0;

				for (int j = 0; j < r && curPixel +j < numPixels; j++)
				{
					Vector<int>^ RGBpixel = ImageHelper::intToRGB(convertedImage->GetAt(curPixel+j));
					valueR += (pow(i, j) *RGBpixel->GetAt(0));
					valueG += (pow(i, j) *RGBpixel->GetAt(1));
					valueB += (pow(i, j) *RGBpixel->GetAt(2));
				}
				shadows->GetAt(i - 1)->InsertPixel(ImageHelper::RGBtoint(valueR % 251, valueG % 251, valueB % 251));
			}
			curX++; 
			if (curX == width)
			{
				curX = 0;
				curY++;
			}
			curPixel += r;
			progress = pConvert +(double) curPixel / (double) numPixels * pShadowing;
			reporter.report(progress);
		}

		if (curX != 0)
		{
			while (curX != width)
			{
				for (int i = 0; i < n; i++)
					shadows->GetAt(i)->InsertPixel(0);
				curX++;
			}
			curY++;
		}
			
		for (int i = 0; i < n; i++)
		{
			shadows->GetAt(i)->setWidth(width);
			shadows->GetAt(i)->setHeight(curY);
		}
		reporter.report(pConvert + pShadowing + pFinishing);
		return shadows;
	});
}

/// <summary>
/// Retrieve the secret.
/// </summary>
/// <param name="shadows">The shadows.</param>
/// <param name="n">The n.</param>
/// <param name="r">The r.</param>
/// <returns></returns>
IAsyncOperationWithProgress<Image^, int>^ SecretSharingManager::CreateSecret(IVector<MetisDll::Image^>^ shadows)
{
	return create_async([this, shadows]
		(progress_reporter<int> reporter, cancellation_token cts) -> MetisDll::Image^ {
		double pLagrange = 80;
		double pRestore = 20;
		double progress;

		int n, r;
		int dif;
		int width = shadows->GetAt(0)->getWidth();
		int height = shadows->GetAt(0)->getHeight();
		MetisDll::Image^ secret = ref new MetisDll::Image();

		//we set the width of the secret based on the shadow width
		secret->setWidth(width);
		int curX = 1, curY = 0;
			
		for (int i = 0; i < shadows->Size; i++)
		{
			Vector<int>^ N= ImageHelper::intToRGB(shadows->GetAt(i)->getPixel(0, 0));
			shadows->GetAt(i)->setN(N->GetAt(2));
			n = N->GetAt(0);
			r = N->GetAt(1);
		}
		dif = shadows->Size-r;
		if (dif < 0)
			r = shadows->Size;
		
			
		
		Vector<int> E;

		//restore the secret by using lagrange interpolation
		while (curY < height)
		{
			vector<Point> pointsR, pointsG, pointsB;
			for (int i = 0; i < shadows->Size; i++)
			{
				int N = shadows->GetAt(i)->getN();
				Vector<int>^ RGBPixel = ImageHelper::intToRGB(shadows->GetAt(i)->getPixel(curX, curY));
				pointsR.push_back(Point(N , RGBPixel->GetAt(0)));
				pointsG.push_back(Point(N , RGBPixel->GetAt(1)));
				pointsB.push_back(Point(N , RGBPixel->GetAt(2)));
			}
			Vector<int>^ temp = ImageHelper::RGBtoint
				(lagrange.CountCoefficient(pointsR), 
				lagrange.CountCoefficient(pointsG), 
				lagrange.CountCoefficient(pointsB));

			for (int y = 0; y < dif; y++)
				temp->RemoveAtEnd();

			for (int item : temp)
				E.Append(item);

			curX++;
			if (curX == width)
			{
				curX = 0;
				curY++;
			}
			progress = (double)(curY*width + curX) / (double)(width*height) * pLagrange;
			reporter.report(progress);
		}

		//restor the format of 250+ to original one
		Vector<int>^ D = ref new  Vector<int>();
		int carryR = 0, carryB = 0, carryG = 0;
		int curPixel = 0; int totalPixel = E.Size;
		curX = 0; curY = 0;
		for (int i = 0; i < totalPixel; i++)
		{
			Vector<int>^ RGBpixel = ImageHelper::intToRGB(E.GetAt(i));
			if (RGBpixel->GetAt(0) == 250 || RGBpixel->GetAt(1) == 250 || RGBpixel->GetAt(2) == 250)
			{
				carryR = RGBpixel->GetAt(0);
				carryG = RGBpixel->GetAt(1);
				carryB = RGBpixel->GetAt(2);
				curPixel++;
				continue;
			}
			D->Append(ImageHelper::RGBtoint
				(carryR + RGBpixel->GetAt(0), carryG + RGBpixel->GetAt(1), carryB + RGBpixel->GetAt(2)));
			carryR = 0; carryB = 0; carryG = 0;

			progress = pLagrange + (double)curPixel++ / (double)totalPixel * pRestore;
			reporter.report(progress);
			curX++;
			if (curX == width)
			{
				curX = 0;
				curY++;
			}
		}
		while (curX != 0)
		{
			D->RemoveAtEnd();
			curX--;
		}

		Image ^ result = ref new Image(D, width, curY);
		progress = 100;
		return result;
	});
}