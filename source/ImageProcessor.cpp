#include "ImageProcessor.hpp"

using namespace cv;
using namespace std;

ImageProcessor::ImageProcessor(int frameHeight, int frameWidth)
{
		//Setup SimpleBlobDetector parameters
		SimpleBlobDetector::Params params;

		//Create Cursor
		Cursor cursor;
		cursor.initSender();

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
		params.filterByCircularity = true;
		params.minCircularity = 0.8;
		params.maxCircularity = 1;

		// Filter by Convexity
		params.filterByConvexity = false;
		params.minConvexity = 0.87;

		// Filter by Inertia
		params.filterByInertia = false;
		//params.minInertiaRatio = 0.01;


		// Set up the detector with default parameters.
		detector = new SimpleBlobDetector(params);

		int cam = initializeCamera(frameHeight, frameWidth);
		if(cam != 0)
		{
				cout << "Error: Camera could not be initialized!!\n";
				cout << "Is there any other program using the camera?" << endl;
		}
}

int ImageProcessor::initializeCamera(int frameHeight, int frameWidth)
{
		
		Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
    Camera.set( CV_CAP_PROP_FRAME_HEIGHT, frameHeight);
    Camera.set( CV_CAP_PROP_FRAME_WIDTH, frameWidth);

		if (!Camera.open())
		{
				cerr<<"Error opening the camera"<<endl;
				return 1;
		}
		else
		{
				return 0;	
		}
}

int ImageProcessor::sendCursor()
{
	cv::Mat image;

	Camera.grab();
	Camera.retrieve(image);

	//cv::imwrite("raspicam_cv_image.jpg",image);
	//cout<<"Image saved at raspicam_cv_image.jpg"<<endl;

	// Detect blobs.
	std::vector<KeyPoint> keypoints;
	detector->detect(image, keypoints);

	std::sort(keypoints.begin(),keypoints.end(),[](KeyPoint a, KeyPoint b)
	{
		return a.response > b.response;
	});

	//cout << "Keypoints detected: " << keypoints.size() << endl;
	if(keypoints.size() > 0)
	{
		//cout << "Keypoint[0] is located at  x =  " << keypoints[0].pt.x;
		//cout << ",  y =  " << keypoints[0].pt.y << endl;
		
		location newLocation = { (int) std::round(keypoints[0].pt.x) , (int) std::round(keypoints[0].pt.y)};
		cout << "found new location : " << newLocation.toString() << endl;

		cursor.sendCursor(newLocation);
		//cout << "Sent new location to fifo" << endl;


	}

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	//Mat im_with_keypoints;
	//drawKeypoints( image, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	// Show blobs
	//imshow("keypoints", im_with_keypoints );
	//cv::imwrite("raspicam_cv_image.jpg",im_with_keypoints);
	//cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
	//waitKey(0);
	return 0;
}

ImageProcessor::~ImageProcessor()
{
		Camera.release();
		delete detector;
}
