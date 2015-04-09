#include "WatershedSegmentation.h"
#include "DicomSeriesTo3dImage.h"
#include "FolderReader.h"
<<<<<<< HEAD
#include "GaussianPyramid.h"
=======
>>>>>>> c2b59aeea18c97ba4222effe37143790b9830f7b
#include <stack>
#include <string>

void interactiveMode();
<<<<<<< HEAD
void downSample(string inputFile);
=======
>>>>>>> c2b59aeea18c97ba4222effe37143790b9830f7b
void threeDimensionDicomSeriesSegment();
void twoDimensionDicomSeriesSegment();
void segment3dImage();
void startSegmentation(string inputFile, string outputFile);

int main(int argc, char ** argv)
{	

<<<<<<< HEAD
	
=======
>>>>>>> c2b59aeea18c97ba4222effe37143790b9830f7b
	if(argc<5)
	{
		interactiveMode();
		return 1;
	}
	

	DicomSeriesTo3dImage converter = DicomSeriesTo3dImage();
	string outputFile = argv[2];

	converter.setInputFolder(argv[1]);
	converter.setOutputFileName(outputFile+"-original");
	converter.setOutputFileFormat("mha");
	converter.convertTo3dFormat();

	
	WatershedSegmentation seg (converter.getOutputFileName()+"."+converter.getOutputFileFormat(), 
		(outputFile+".mha"),atof(argv[3]), atof(argv[4]));

	seg.performSegmentation();

	
   return 0;
}

void interactiveMode()
{
	string userSelection = "";

	do
	{
		cout<<"Please select from the following:"<<endl;
		cout<<"Enter 1 to segment a 2d Dicom series image as a single 3d image"<<endl;
		cout<<"Enter 2 to segment a single 3d image file"<<endl;
		cout<<"Enter 3 to segment each 2d image in a dicom series one by one"<<endl;
		cout<<"Enter e to exit"<<endl;
		cin >> userSelection;
		if(userSelection.compare("e") == 0) break;
		else if(userSelection.compare("1") == 0) threeDimensionDicomSeriesSegment();
		else if(userSelection.compare("2") == 0) segment3dImage();
		else if(userSelection.compare("3") == 0) twoDimensionDicomSeriesSegment();

	}while(1);
}

void threeDimensionDicomSeriesSegment()
{
	string inputFolder;
	string outputFile;
	string outputFileFormat;

	cout<<"Enter the dicom series folder:"<<endl;
	cin>>inputFolder;
	cout<<"Enter the output file name(not with format):"<<endl;
	cin>>outputFile;
	cout<<"Enter the output file format:"<<endl;
	cin>>outputFileFormat;

	DicomSeriesTo3dImage converter = DicomSeriesTo3dImage();
	

	converter.setInputFolder(inputFolder);
	converter.setOutputFileName(outputFile+"-original");
	converter.setOutputFileFormat(outputFileFormat);
	converter.convertTo3dFormat();

	startSegmentation(converter.getOutputFileName()+"."+outputFileFormat, 
		(outputFile+"."+outputFileFormat));
	

}

//this might throw exception as we need to change dimension inside the WatershedSegmentaion class
// to support 2d.
void twoDimensionDicomSeriesSegment()
{
	string inputFolder;
	string outputFolder;
	float threshold;
	float level;

	cout<<"Enter the dicom series folder:"<<endl;
	cin>>inputFolder;
	cout<<"Enter the output folder:"<<endl;
	cin>>outputFolder;
	cout<<"Enter the lower threshold level :"<<endl;
	cin>>threshold;
	cout<<"Enter the scale level:"<<endl;
	cin>>level;

	FolderReader fdReader(inputFolder);
	stack<string> files;

	inputFolder.append("/");
	outputFolder.append("/");
	files = fdReader.getAllFiles();
  
	for(int i=0; i<files.size(); i++)
	{  
		
		WatershedSegmentation seg (inputFolder+files.top(), outputFolder+files.top(), threshold, level);
		seg.dimension=2;
		seg.performSegmentation();
		files.pop();
		system("PAUSE");
		//inputImageFileFullPath = "";
	}

}

void segment3dImage()
{
	string inputFile;
	string outputFile;
	string outputFileFormat;

	cout<<"Enter the complete 3d input file (along with format):"<<endl;
	cin>>inputFile;
	cout<<"Enter the output file name(not with format):"<<endl;
	cin>>outputFile;
	cout<<"Enter the output file format:"<<endl;
	cin>>outputFileFormat;


	startSegmentation(inputFile, 
		(outputFile+"."+outputFileFormat));
}

void startSegmentation(string inputFile, string outputFile)
{
	float threshold;
	float level;

	cout<<"Enter the lower threshold level :"<<endl;
	cin>>threshold;
	cout<<"Enter the scale level:"<<endl;
	cin>>level;

<<<<<<< HEAD
	GaussianPyramid gm = GaussianPyramid(inputFile, "down_sampled_"+inputFile);
	gm.execute();

	WatershedSegmentation seg ("down_sampled_"+inputFile, outputFile, threshold, level);
=======
	WatershedSegmentation seg (inputFile, outputFile, threshold, level);
>>>>>>> c2b59aeea18c97ba4222effe37143790b9830f7b

	seg.performSegmentation();

}

