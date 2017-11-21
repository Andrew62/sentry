//
//  extraction.hpp
//  Sentry
//
//  Created by Andrew Woizesko on 3/4/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

#ifndef extraction_hpp
#define extraction_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>

// consolidating image operations
namespace utils {
    void process_frame(cv::Mat& rawImage, cv::Mat& processed);
    std::string get_datestamp();
};

#endif /* extraction_hpp */
