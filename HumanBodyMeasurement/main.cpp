#include <opencv2\core\core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include<opencv\cv.h>
#include <iostream>
#include "ImageFileIO.h"
//#include <windows.h>
//#include <direct.h>


#include"BodyMeasurements.h"

using namespace GymBodyFitness::Process::Module;


using namespace std;
using namespace cv;


static cv::vector<cv::Point> v_pLftFeaturePoints, v_pRgtFeaturePoints;

static bool bMouseFlag = 0;

static int nPointnumber = 0;

void on_mouse(int e, int x, int y, int d, void *ptr)
{
	
	cv::Mat *oMatmarkingImage = (cv::Mat*)ptr;
	cv::Mat oMatInputBFImage = *oMatmarkingImage;
	cv::vector<cv::Point> cordinatepoints ;
	imshow("Human Body Measurement", *oMatmarkingImage);

	
		
	if (e == EVENT_LBUTTONDOWN)
	{
		
		{
			nPointnumber += 1;
			printf("%d %d \n", x, y);
			cv::Point pLftPoint;
			pLftPoint.x = x;
			pLftPoint.y = y;			
			v_pLftFeaturePoints.push_back(pLftPoint);	
			cv::putText(*oMatmarkingImage, to_string(nPointnumber), cv::Point(x, y),
				FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(255, 255, 0), 2,4);

			cv::circle(*oMatmarkingImage, cv::Point(x, y), 0.5, cv::Scalar(0, 0, 255),4);			
		} 
		if (20 == nPointnumber )
		{
			cv::destroyAllWindows();
		}
	}

	
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Enter Correct number of Command Line Arguments" << endl;
		system("PAUSE");
		return -1;
	}



	cout << " ---------------------------------------------------------- " << endl;
	cout << "                  Human Body Measurement                    " << endl;
	cout << "                Hungry Heart Technology Services            " << endl;	
	cout << " ----------------------------------------------------------  " << endl;
	cout << endl << endl;

	string RootFolder1(argv[1]);
	if ((FileIO::ValidDirectory(RootFolder1)))
	{
		cout << "Please Provide Valid Human Image" << endl;
		system("PAUSE");
		return -1;
	}

	///Read the Human Image 
	Mat oMatInputImg = imread(argv[1]);
	if (oMatInputImg.empty())
	{
		cout << "Please Provide valid Image Path  " << endl;
		system("PAUSE");
		return -1;
	}



	int nResizeNumber = 1;
	double dPixelToMeterFactor = 0.063344;
	//To give an input image 
	//Mat oMatInputImg = imread("Front.jpg");
	//cv::resize(oMatInputImg, oMatInputImg, cv::Size(oMatInputImg.cols / nResizeNumber, oMatInputImg.rows / nResizeNumber));
	cv::resize(oMatInputImg, oMatInputImg, cv::Size(600,800));
	/*cv::imshow("resizedimage", oMatInputImg);
	cv::waitKey(0);*/

	//Create Result folder to save ouput images
	string strImagesFolderPath = argv[1];
	size_t found = strImagesFolderPath.find_last_of("/\\");
	string FilePath = strImagesFolderPath.substr(0, found);

	strImagesFolderPath = FilePath + "\\MeasurementResults";
	_mkdir(strImagesFolderPath.c_str());

	Size s_BrightSize = oMatInputImg.size();
	//Size s_FluorSize = oMatFluorescenceFieldImg.size();
	Mat oMatReferenceImage(s_BrightSize.height, s_BrightSize.width, CV_8UC3);
	// Move right boundary to the left.
	oMatReferenceImage.adjustROI(0, 0, 0, s_BrightSize.width);
	oMatInputImg.copyTo(oMatReferenceImage);
	// Move the left boundary to the right, right boundary to the right.
	oMatReferenceImage.adjustROI(0, 0, s_BrightSize.width, s_BrightSize.height);
	
	////Create a window
	namedWindow("Human Body Measurement", CV_WINDOW_NORMAL);

	//set the callback function for any mouse event
	
	//cv::vector<cv::Point> v_pFeaturePoints;	
	
		setMouseCallback("Human Body Measurement", on_mouse, &oMatReferenceImage);
		waitKey(0);
	
	 ////exception handling 
		if (20 >v_pLftFeaturePoints.size())
		{
			cout << "Minimum 24 points should be marked " << endl;
		}
	
		imwrite(strImagesFolderPath + "\\MarkedImage.jpg", oMatReferenceImage);
	CBodyMeasurements *pcObj = new CBodyMeasurements();

	cv::Mat oMatOrginalImage =   oMatInputImg.clone();
	pcObj->PerformMeasurements(v_pLftFeaturePoints, nResizeNumber, dPixelToMeterFactor, oMatOrginalImage, strImagesFolderPath);


	
	
	
	return 0;
}