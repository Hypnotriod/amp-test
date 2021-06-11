/* 
 * File:   main.cpp
 * Author: Ilya Pikin
 *
 * Created on June 11, 2021, 3:56 PM
 */

#include <cstdlib>
#include <iostream>

#include "WavFileReader.h"
#include "WavFileWriter.h"
#include "AmpProcessor.h"
#include "AmpWindow.h"

using namespace std;

const double window[] = {1, 2, 1.5, 1, 1};

int main(int argc, char** argv) {
    AmpProcessor ampProcessor;
    AmpProcessor::Status status;
    AmpWindow ampWindow(window, sizeof(window) / sizeof(window[0]), 32);
    
    status = ampProcessor.process("data/input.wav", "data/output.wav", ampWindow);
    
    if (status != AmpProcessor::OK) {
        cout << "Failed.";
        return -1;
    }
    
    cout << "Done OK.";
    return 0;
}

