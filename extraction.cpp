//
//  extraction.cpp
//  Sentry
//
//  Created by Andrew Woizesko on 3/4/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

#include "extraction.hpp"
#include <opencv2/opencv.hpp>


void utils::process_frame(cv::Mat& rawImage, cv::Mat& processed){
    // decode data stream
    cv::Mat img = cv::imdecode(rawImage, CV_LOAD_IMAGE_COLOR);
    
    // flip and mirror image
    cv::flip(img, img, 1);
    cv::transpose(img, img);
    
    cv::resize(img, processed, cv::Size(), 2, 2, cv::INTER_CUBIC);
}



