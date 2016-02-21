#include <iostream>
#include <fstream>
#include <opencv2/imgproc/imgproc.hpp>
#include <raspicam/raspicam_cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>
#include "Cursor.hpp"

using namespace cv;
using namespace std;



class ImageProcessor
{
public:
	ImageProcessor(int frameHeight, int frameWidth);
	~ImageProcessor();

	int sendCursor();
	
private:
	int initializeCamera(int frameHeight, int frameWidth);
	raspicam::RaspiCam_Cv Camera;
	SimpleBlobDetector* detector;
	Cursor cursor;
};


