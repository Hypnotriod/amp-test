
/* 
 * File:   AmpProcessor.cpp
 * Author: Ilya Pikin
 */

#include "AmpProcessor.h"
#include "WavFileReader.h"
#include "WavFileWriter.h"

AmpProcessor::AmpProcessor() {
}

AmpProcessor::~AmpProcessor() {
}

AmpProcessor::Status AmpProcessor::process(
        const char * srcPath, const char * destPath, double factor, size_t ratio, double threshold) {
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

        for (size_t n = ratio; n > 0; n--) {
            for (size_t i = 0; i < samplesRead; i++) {
                sample = ioSampleBuff[i] > 0 ? ioSampleBuff[i] : -ioSampleBuff[i];
                sample = (sample - sample * sample * 0.5) * 2;
                if (ioSampleBuff[i] < 0) sample = -sample;
                ioSampleBuff[i] = ioSampleBuff[i] * (1 - factor) + sample * factor;
                if (n == 1) {
                    ioSampleBuff[i] *= threshold;
                    if (ioSampleBuff[i] < -1) ioSampleBuff[i] = -1;
                    if (ioSampleBuff[i] > 1) ioSampleBuff[i] = 1;
                }
            }
        }
        

        if (writer.write(samplesRead, ioSampleBuff) != WavFileWriter::OK)
            return ERROR;

        if (readerStatus == WavFileReader::END_OF_FILE)
            break;
    }

    return readerStatus == WavFileReader::READ_ERROR ? ERROR : OK;
}
