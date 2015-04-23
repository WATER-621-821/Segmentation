#ifndef ImageCropper_H_
#define ImageCropper_H_


using namespace std;

#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"
#include "itkCropImageFilter.h"
#include <string>

class ImageCropper
{

	private:
		string inputImage;
		string outputImage;


	public:

		ImageCropper(string inImg, string otImg);
		void crop();

		

};


#endif 