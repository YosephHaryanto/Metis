#pragma once

#include "Image.h"

namespace Metis {
	ref class DataHidingManager sealed
	{
	public:
		DataHidingManager();
	private:
		double SQRT2o2;
		double alpha(int i){ return i == 0 ? SQRT2o2 * 0.5 : 0.5; } 
		double cosine[8][8];

		int GammaFactor(std::vector<double> in);
		std::vector<double > DCT(std::vector<int> B);

		std::vector<int> SecretImageDifferencing(Metis::Image CoverImage);
		std::vector<int> CoverImageDifferencing(Metis::Image CoverImage);
		
		Metis::Image HideData(Metis::Image CoverImage, Metis::Image Payload, int key);


	};
}

