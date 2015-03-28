
#include <sstream>
#include  "WatershedSegmentation.h"

WatershedSegmentation :: WatershedSegmentation( string filename,float thres, float lev)
{
	this->inputFileName = filename;
	this->threshold = thres;
	this->level = lev;
	this->dimension = 3;
}


WatershedSegmentation :: WatershedSegmentation( string filename, string otflname, float thres, float lev)
{
	this->inputFileName = filename;
	this->threshold = thres;
	this->level = lev;
	this->dimension = 3;

	std::ostringstream thresholdbuff;
	std::ostringstream levelbuff;
	thresholdbuff<<thres;
	levelbuff<<level;

	this->outputFileName = otflname;
    /*std::size_t pos = otflname.find(".");     
    std::string extension =  otflname.substr (pos); 

	this->outputFileName = otflname.substr(0, pos);
    this->outputFileName.append(thresholdbuff.str());
	this->outputFileName.append("-");
	this->outputFileName.append(levelbuff.str());
	this->outputFileName.append(extension);*/
}

void WatershedSegmentation:: performSegmentation()
{

	typedef itk::Image< InternalPixelType,  WatershedSegmentation::dimension3d >  InternalImageType;
  	typedef itk::Image< RGBPixelType, WatershedSegmentation::dimension3d>  RGBImageType;

	typedef  itk::ImageFileReader< InternalImageType   >  ReaderType;
	typedef  itk::ImageFileReader< RGBImageType   >  RGBReaderType;
	typedef  itk::ImageFileWriter< RGBImageType  >  RGBWriterType;
	typedef  itk::ImageFileWriter< InternalImageType >  WriterType;

	InternalImageType::Pointer segmentedImage;
	RGBImageType::Pointer coloredSegmentedImage;

    ReaderType::Pointer reader = ReaderType::New();
	RGBWriterType::Pointer writer = RGBWriterType::New();


	reader->SetFileName( this->inputFileName );
	writer->SetFileName(this->outputFileName);		 
    InternalImageType::Pointer image = reader->GetOutput();
		
			  //
  //  Instantiate the GradientMagnitude image filter
  //
    typedef   itk::GradientMagnitudeRecursiveGaussianImageFilter<
                                                     InternalImageType,
                                                     InternalImageType
                                                          > GradientMagnitudeFilterType;

    GradientMagnitudeFilterType::Pointer gradienMagnitudeFilter = GradientMagnitudeFilterType::New();

    gradienMagnitudeFilter->SetInput( image );
    gradienMagnitudeFilter->SetSigma( 1.0 );


  //
  //  Instantiate the Watershed filter
  //

    typedef  itk::WatershedImageFilter<
                              InternalImageType
                                            > WatershedFilterType;

    WatershedFilterType::Pointer watershedFilter = WatershedFilterType::New();

    watershedFilter->SetInput( gradienMagnitudeFilter->GetOutput() );

    watershedFilter->SetThreshold( this->threshold );
    watershedFilter->SetLevel( this->level );


  //
  //  Instantiate the filter that will encode the label image
  //  into a color image (random color attribution).
  //

    typedef itk::Functor::ScalarToRGBPixelFunctor<
                                           unsigned long
                                                    > ColorMapFunctorType;

    typedef WatershedFilterType::OutputImageType  LabeledImageType;

    typedef itk::UnaryFunctorImageFilter<
                                LabeledImageType,
                                RGBImageType,
                                ColorMapFunctorType
                                                > ColorMapFilterType;

    ColorMapFilterType::Pointer colorMapFilter = ColorMapFilterType::New();

    colorMapFilter->SetInput(  watershedFilter->GetOutput() );
	coloredSegmentedImage =  colorMapFilter->GetOutput() ;

    writer->SetInput(coloredSegmentedImage );

    try
    {
        writer->Update();
    }
    catch( itk::ExceptionObject & excep )
    {
        std::cerr << "Exception caught !" << std::endl;
        std::cerr << excep << std::endl;
    }

}
