#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main ( int argc,char **argv ) {

	raspicam::RaspiCam_Cv Camera;
	cv::Mat image;
	int nCount = 3;

	Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
	Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 1024);
	Camera.set( CV_CAP_PROP_FRAME_WIDTH, 1024);

	if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;}
	int i = 0;
	while(i < nCount)
	{
		Camera.grab();
		Camera.retrieve(image);
	i++;
	}
	Camera.release();

	cv::imwrite("raspicam_cv_image.jpg",image);
	cout<<"Image saved at raspicam_cv_image.jpg"<<endl;


	cout<<"Reading image for detection"<<endl;
	// Read image
	Mat im = imread( "raspicam_cv_image.jpg", IMREAD_GRAYSCALE);


	//Setup SimpleBlobDetector parameters
	SimpleBlobDetector::Params params;

	//Filter by Color : 255 for light and 0 for dark
	params.blobColor = 255;

	// Change thresholds
	params.minThreshold = 50;
	params.maxThreshold = 500;

	// Filter by Area.
	params.filterByArea = false;
	params.minArea = 10;
	params.maxArea = 300;

	// Filter by Circularity
	params.filterByCircularity = false;
	params.minCircularity = 0.8;
	params.maxCircularity = 1;

	// Filter by Convexity
	params.filterByConvexity = false;
	params.minConvexity = 0.87;

	// Filter by Inertia
	params.filterByInertia = false;
	//params.minInertiaRatio = 0.01;


	// Set up the detector with default parameters.
	SimpleBlobDetector detector(params);

	// Detect blobs.
	std::vector<KeyPoint> keypoints;
	detector.detect( im, keypoints);

	cout << "Keypoints detected: " << keypoints.size() << endl;
	cout << "Keypoint[0] is located at  x =  " << keypoints[0].pt.x;
	cout << ",  y =  " << keypoints[0].pt.y << endl;
	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	// Show blobs
	//imshow("keypoints", im_with_keypoints );
	cv::imwrite("raspicam_cv_image.jpg",im_with_keypoints);
	cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
	//waitKey(0);
}
