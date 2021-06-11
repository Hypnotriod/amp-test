
/* 
 * File:   AmpProcessor.cpp
 * Author: Ilya Pikin
 */

#include "AmpProcessor.h"
#include "WavFileReader.h"
#include "WavFileWriter.h"
#include "AmpWindow.h"

AmpProcessor::AmpProcessor() {
}

AmpProcessor::~AmpProcessor() {
}

AmpProcessor::Status AmpProcessor::process(const char * srcPath, const char * destPath, AmpWindow & ampWindow) {
    WavFileReader reader;
    WavFileReader::Status readerStatus;
    WavFileWriter writer;
    
    double ioSampleBuff[IO_SAMPLE_BUFF_SIZE];
    size_t samplesRead;
    double sample;

    if (reader.open(srcPath) != WavFileReader::OK || writer.open(destPath) != WavFileWriter::OK)
        return ERROR;

    writer.writeHeader(*reader.getHeader());
    
    while (true) {
        readerStatus = reader.read(IO_SAMPLE_BUFF_SIZE, ioSampleBuff, &samplesRead);
        if (readerStatus == WavFileReader::READ_ERROR)
            break;
        
        for (size_t i = 0; i < samplesRead; i++) {
            ioSampleBuff[i] = ampWindow.apply(ioSampleBuff[i]);
        }
        
        if (writer.write(samplesRead, ioSampleBuff) != WavFileWriter::OK)
            return ERROR;
        
        if (readerStatus == WavFileReader::END_OF_FILE)
            break;
    }
    
    return readerStatus == WavFileReader::READ_ERROR ? ERROR : OK;
}
