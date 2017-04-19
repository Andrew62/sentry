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
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>


// consolidating image operations
namespace utils {
    dlib::cv_image<dlib::bgr_pixel> process_frame(cv::Mat& rawImage);
};

#endif /* extraction_hpp */
