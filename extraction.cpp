//
//  extraction.cpp
//  Sentry
//
//  Created by Andrew Woizesko on 3/4/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

#include "extraction.hpp"
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>


void utils::get_face_chips(const dlib::cv_image<dlib::bgr_pixel>& img,
                           const std::vector<dlib::rectangle>& detections,
                           dlib::array<dlib::array2d<dlib::bgr_pixel>>& chips){

    for (unsigned long j = 0; j < detections.size(); j++){
        dlib::array2d<dlib::bgr_pixel> chip;
        dlib::extract_image_chip(img, detections[j], chip);
        chips.push_back(chip);
    };
    
}

dlib::cv_image<dlib::bgr_pixel> utils::process_frame(cv::Mat& rawImage){
    // decode data stream
    cv::Mat img = cv::imdecode(rawImage, CV_LOAD_IMAGE_COLOR);
    
    // flip and mirror image
    cv::flip(img, img, 1);
    cv::transpose(img, img);
    
    cv::resize(img, img, cv::Size(), 2, 2, cv::INTER_CUBIC);
    
    dlib::cv_image<dlib::bgr_pixel> d_image(img);
    return d_image;
}

void utils::save_chips(const char* outdir,
                       int& imageId, dlib::cv_image<dlib::bgr_pixel>& d_image,
                       std::vector<dlib::rectangle>& detections){
    
    dlib::array<dlib::array2d<dlib::bgr_pixel>> face_chips;
    
    utils::get_face_chips(d_image, detections, face_chips);
    if (detections.size() > 0){
        // save each face chip for classification
        for (long idx = 0; idx < face_chips.size(); idx++){
            std::string fname = outdir + std::to_string(imageId) + ".jpg";
            dlib::save_jpeg(face_chips[idx], fname);
        }
    }

};


