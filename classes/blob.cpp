#include "blob.hpp"

// blob::blob(){

// }


void blob::test_blob(cv::Mat frame)
{	
	cv::Mat im;



	// Setup SimpleBlobDetector parameters.
	cv::SimpleBlobDetector::Params params;
	 
	// Change thresholds
	params.minThreshold = 150;
	params.maxThreshold = 250;
	 
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 400;
	 
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.4;
	 
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.01;
	 
	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;
	 
	cv::SimpleBlobDetector detector(params);


			
	        im = frame;
	        cv::imshow("im", im );

	
			// Detect blobs.
			std::vector<cv::KeyPoint> keypoints;
			detector.detect( im, keypoints);
			//std::cout << "X = " << keypoints << std::endl;
			
			cv::Mat im_with_keypoints;

			
			cv::drawKeypoints( im, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

			cv::Point2f center;
			float radius;

			if (keypoints.size() != 0)
			{
				center = keypoints[0].pt;
				radius = keypoints[0].size;

				std::cout << "X = " << center.x << std::endl;
				std::cout << "Y = " << center.y << std::endl;
				std::cout << "Radius = " << radius << std::endl;
				std::cout << "Area = " << 3.14159*radius*radius << std::endl;


			}

			//std::cout << "Y = " << cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS << std::endl;


			// Show blobs
			cv::imshow("keypoints.", im_with_keypoints );
		
		
	    
		//}

}
