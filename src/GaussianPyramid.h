#ifndef GaussianPyramid_H_
#define GaussianPyramid_H_


using namespace std;

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkShrinkImageFilter.h"
#include "itkSmoothingRecursiveGaussianImageFilter.h"
#include "itkSmartPointer.h"
#include <string>

class GaussianPyramid
{

	private:
		string inputImage;
		string outputImage;


	public:

		GaussianPyramid(string inImg, string otImg);
		void execute();

		

};


#endif 