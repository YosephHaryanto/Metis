#include "pch.h"
#include "ImageEncryptionManager.h"
#include "Image.h"

#include <ppltasks.h>

using namespace MetisDll;
using namespace Windows::Foundation;
using namespace concurrency;

ImageEncryptionManager::ImageEncryptionManager()
{
	
}

//declaring the constant of alfa beta and key for the encryption and decryption
double ImageEncryptionManager::alfa(1.1);

double ImageEncryptionManager::beta(5);

double ImageEncryptionManager::x0(0.987654321012345);

IAsyncActionWithProgress<int>^ ImageEncryptionManager::Decrypt(Image imageData)
{
	return create_async([this,&imageData]
		(progress_reporter<int> reporter, cancellation_token cts) {
		//skip the first 100 x
		double xnow = NCA(x0);
		for (int i = 2; i <= 100; i++)
		{
			xnow = NCA(xnow);
		}

		int x = 0, y = 0;

		//loop until the end of the pixel
		while (y < imageData.getHeight())
		{
			// three times skipping
			for (int i = 0; i < 3; i++)
			{
				xnow = NCA(xnow);
			}

			double frac = xnow;
			for (int i = 0; i < 5; i++)
			{
				if (y >= imageData.getHeight())
					break;

				double intByte;
				frac = modf(frac * 1000, &intByte);
				int byteData = (int)intByte % 256;
				imageData.ModifyPixel(x, y, byteData ^ imageData.getPixel(x, y));

				x++;
				if (x == imageData.getWidth())
				{
					x = 0; y++;
				}
			}
		}
	});
}

IAsyncActionWithProgress<int>^ ImageEncryptionManager::Encrypt(Image imageData)
{
	return create_async([this, &imageData ]
		(progress_reporter<int> reporter, cancellation_token cts) {
		//skip the first 100 x
		double xnow = NCA(x0);
		for (int i = 2; i <= 100; i++)
		{
			xnow = NCA(xnow);
		}

		int x = 0, y = 0;

		//loop until the end of the pixel
		while (y < imageData.getHeight())
		{
			// three times skipping
			for (int i = 0; i < 3; i++)
			{
				xnow = NCA(xnow);
			}

			double frac = xnow;
			for (int i = 0; i < 5; i++)
			{
				if (y >= imageData.getHeight())
					break;

				double intByte;
				frac = modf(frac * 1000, &intByte);
				int byteData = (int)intByte % 256;
				imageData.ModifyPixel(x, y, byteData ^ imageData.getPixel(x, y));

				x++;
				if (x == imageData.getWidth())
				{
					x = 0; y++;
				}
			}
		}
	});
}

double ImageEncryptionManager::NCA(double Xn)
{
	double miu = 1 - pow(beta, -4);
	double lamda = miu * cotan(alfa / (1.0 + beta)) * pow((1.0 + 1.0 / beta), beta);
	return lamda *tan(alfa * Xn) * pow((1 - Xn), beta);
}
