
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include<opencv\cv.h>
#include <iostream>



using namespace std;
using namespace cv;




///// nmouse flag is 1 then manual box marking mode or if its zero its hardcoded mode 

void my_mouse_callback(int event, int x, int y, int flags, void* param);

bool destroy = false;
Rect box;
bool drawing_box = false;

void draw_box(Mat * img, Rect rect)
{
	rectangle(*img, Point(box.x, box.y), Point(box.x + box.width, box.y + box.height), Scalar(255, 255, 255), 1);

	Rect rect2 = Rect(box.x, box.y, box.width, box.height);
}


void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
	Mat* frame = (Mat*)param;
	imshow("Grabcut Box", *frame);


	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
	{
							   if (drawing_box)
							   {
								   box.width = x - box.x;
								   box.height = y - box.y;
							   }
	}
		break;

	case CV_EVENT_LBUTTONDOWN:
	{   drawing_box = true;
	box = Rect(x, y, 0, 0);
	}
		break;

	case CV_EVENT_LBUTTONUP:
	{   drawing_box = false;
	if (box.width < 0)
	{
		box.x += box.width;
		box.width *= -1;
	}

	if (box.height < 0)
	{
		box.y += box.height;
		box.height *= -1;
	}
	draw_box(frame, box);
	}
		break;

	default:
		break;
	}
}





int main(int argc, char** argv)
{
	if (argc < 3)
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
	string sInputMode = argv[1];

	int nMouseFlag = std::stoi(sInputMode);
	string RootFolder1(argv[1]);
	/*if ((FileIO::ValidDirectory(RootFolder1)))
	{
	cout << "Please Provide Valid Human Image" << endl;
	system("PAUSE");
	return -1;
	}*/

	///Read the Human Image 
	Mat oMatInputImg = imread(argv[2]);
	//Mat oMatInputImg = imread("D:\\P1-1.tif");
	//Mat oMatInputImg = imread("D:\\P2.tif");
	
	if (oMatInputImg.empty())
	{
		cout << "Please Provide valid Image Path  " << endl;
		system("PAUSE");
		return -1;
	}



	// Open another image
	Mat image;
	image = oMatInputImg;
	cv::Mat result; // segmentation result (4 possible values)
	cv::Mat bgModel, fgModel; // the models (internally used)
	cv::Rect rectangle;
	if (1 == nMouseFlag)
	{
		//////Create a window
		namedWindow("Grabcut Box", CV_NORMAL);
		setMouseCallback("Grabcut Box", my_mouse_callback, &image);
		waitKey(0);
		rectangle.x = box.x,
		rectangle.y = box.y;
		rectangle.width = box.width;
		rectangle.height = box.height;
			
	}

	else
	{
	////define bounding rectangle 
	rectangle.x = 125,
	rectangle.y = 140;
	rectangle.width = image.cols - 250 ;
	rectangle.height = image.rows;

	}






	// GrabCut segmentation
	cv::grabCut(image,    // input image
		result,   // segmentation result
		rectangle,// rectangle containing foreground 
		bgModel, fgModel, // models
		1,        // number of iterations
		cv::GC_INIT_WITH_RECT); // use rectangle
	cout << "oks pa dito" << endl;
	// Get the pixels marked as likely foreground
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	// Generate output image
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	image.copyTo(foreground, result); // bg pixels not copied

	//////draw rectangle on original image
	cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);
	cv::namedWindow("Image", CV_NORMAL);
	cv::imshow("Image", image);

	string sInputpath = argv[2];
	size_t found = sInputpath.find_last_of("/\\");
	string FilePath = sInputpath.substr(0, found);

	cv::imwrite(FilePath + "\\ManualMarkedGC.jpg", image);

	// display result
	cv::namedWindow("Segmented Image", CV_NORMAL);
	cv::imshow("Segmented Image", foreground);

	cv::imwrite(FilePath + "\\Segmented.jpg", foreground);

	waitKey();
	return 0;
}
