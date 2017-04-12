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
    void get_face_chips(const dlib::cv_image<dlib::bgr_pixel>& img,
                        const std::vector<dlib::rectangle>& detections,
                        dlib::array<dlib::array2d<dlib::bgr_pixel>>& chips);
    
    dlib::cv_image<dlib::bgr_pixel> process_frame(cv::Mat& rawImage);
    
    void save_chips(const char* outdir, int& imageId,
                     dlib::cv_image<dlib::bgr_pixel>& d_image,
                     std::vector<dlib::rectangle>& detections);
};

#endif /* extraction_hpp */
