#pragma once
#include <math.h>
#include "Image.h"

namespace MetisDll
{
	class ImageEncryptionManager sealed
	{
	public:

		ImageEncryptionManager();
		Windows::Foundation::IAsyncActionWithProgress<int>^ Encrypt(Image imageData);
		Windows::Foundation::IAsyncActionWithProgress<int>^ Decrypt(Image imageData);
	private:
		
		static double alfa,beta,x0;

		static double NCA( double Xn);

		static double cotan(double i){ return 1.0 / tan(i); }
	};
}

