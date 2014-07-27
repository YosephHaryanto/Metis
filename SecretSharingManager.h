#pragma once

#include <collection.h>
#include "Image.h"

namespace MetisDll {
	public ref class SecretSharingManager sealed
	{
	public:
		Windows::Foundation::IAsyncOperationWithProgress<Windows::Foundation::Collections::IVector<MetisDll::Image^>^, int >^ 
			CreateShadow(MetisDll::Image^ imageData, int n, int r);
		Windows::Foundation::IAsyncOperationWithProgress<MetisDll::Image^, int>^ 
			CreateSecret(Windows::Foundation::Collections::IVector<MetisDll::Image^>^ shadows);
	
	};
}
