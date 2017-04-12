//
//  main.cpp
//  Sentry
//
//  Created by Andrew Woizesko on 2/11/17.
//  Copyright © 2017 Andrew Woizesko. All rights reserved.
//

// the standard stuff
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring> 

// opencv mat object
#include <opencv2/opencv.hpp>

// dlib>
#include <dlib/opencv.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include <dlib/image_processing/frontal_face_detector.h>

// socket wrapper object
#include "net.hpp"
#include "extraction.hpp"


int main(int argc, const char * argv[]) {
    
    std::cout << "Starting Sentry" << std::endl;
    if (argc == 2){
        std::cout << "Saving images to: " << argv[1] << std::endl;
    }
    
    struct sockaddr_storage their_addr;
    
    // Config for socket. Listen on port 8123 by default
    char* listenPort = "8123";
    
    // backlog foc connections
    int backlog = 1;
    
    // create the simple socket
    net::Socket sockt = net::Socket(listenPort);
    
    // bind to  port
    sockt.bindSock();
    
    // look for connections
    sockt.startListening(backlog);
    
    // start accepting data from this new file descriptor
    sockt.acceptData(their_addr);
    
    // size of the image from the client
    int32_t image_size = 0;
    
    // object to store raw image data
    cv::Mat rawImage;
    
    // initialize the detector
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    
    std::cout << "Capturing..." << std::endl;
    
    // for writing out images 
    int image_id = 1;
    
    while (true){
        
        // retrieve image size
        sockt.getData(&image_size, 4, NULL);
        
        if (image_size > 0) {
        
            rawImage.create(1, image_size, CV_8UC1);

            sockt.getData(rawImage.data, image_size, MSG_WAITALL);
            
            dlib::cv_image<dlib::bgr_pixel> d_image = utils::process_frame(rawImage);
            
            std::vector<dlib::rectangle> detections = detector(d_image);
            
            std::cout << "Number of detections: " << detections.size() << std::endl;
            
            if (argc == 2){
                utils::save_chips(argv[1], image_id, d_image, detections);
            }

            image_id++;
            
            // clear the raw image b/c the size might change(?)
            // not sure if i need to do this
            memset(&rawImage, 0x0, sizeof(rawImage));
            
        } else {
            std::cout << "No message yet" << std::endl;
            
        }
        // pause for half a second
        image_size = 0;
        usleep(1000);
    };
    
    return 0;

}

