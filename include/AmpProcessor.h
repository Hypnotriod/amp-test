
/* 
 * File:   AmpProcessor.h
 * Author: Ilya Pikin
 */

#ifndef AMPPROCESSOR_H
#define AMPPROCESSOR_H

#include <cstdlib>

class AmpProcessor {
public:
    AmpProcessor();
    virtual ~AmpProcessor();

    const size_t IO_SAMPLE_BUFF_SIZE = 4096;

    enum Status {
        OK = 0,
        ERROR = 1,
    };

    Status process(const char * srcPath, const char * destPath, double factor, double threshold);
private:

};

#endif /* AMPPROCESSOR_H */
