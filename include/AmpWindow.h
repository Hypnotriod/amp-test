
/* 
 * File:   AmpWindow.h
 * Author: Ilya Pikin
 */

#ifndef AMPWINDOW_H
#define AMPWINDOW_H

#include <cstdlib>


class AmpWindow {
public:
    AmpWindow(const double * window, size_t windowSize, size_t reactionSteps);
    virtual ~AmpWindow();
    double apply(double sample);
private:
    double * levelReaction;
    const double * window;
    const size_t windowSize;
    const size_t reactionSteps;
};

#endif /* AMPWINDOW_H */
