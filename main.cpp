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

/**
 * threshold (peak) value = 1 / (2 ^ (db / 6))
 */

using namespace std;

int main(int argc, char** argv) {
    AmpProcessor ampProcessor;
    AmpProcessor::Status status;
    
    status = ampProcessor.process("data/input.wav", "data/output.wav", 1.5, 0.594);
    
    if (status != AmpProcessor::OK) {
        cout << "Failed.";
        return -1;
    }
    
    cout << "Done OK.";
    return 0;
}

