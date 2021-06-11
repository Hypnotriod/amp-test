
/* 
 * File:   AmpWindow.cpp
 * Author: Ilya Pikin
 */

#include "AmpWindow.h"

AmpWindow::AmpWindow(const double * window, size_t windowSize, size_t reactionSteps) 
    : window(window), windowSize(windowSize), reactionSteps(reactionSteps) {
    levelReaction = new double[reactionSteps];
}

AmpWindow::~AmpWindow() {
    delete[] levelReaction;
}

double AmpWindow::apply(double sample) {
    double level = sample * (windowSize - 1);
    
    for (size_t i = 0; i < reactionSteps - 1; i++) {
        levelReaction[i] = levelReaction[i + 1];
    }
    levelReaction[reactionSteps - 1] = level;
    level = 0;
    for (size_t i = 0; i < reactionSteps; i++) {
        level += levelReaction[i];
    }
    level /= reactionSteps;
    
    if (level < 0) level *= -1;
    int index = level;
    double coeffA = level - index;
    double coeffB = 1.f - coeffA;
    double ampFactor = (window[index] * coeffA + window[index + 1] * coeffB);
    double result = ampFactor * sample;
    if (result < -1) result = -1;
    if (result > 1) result = 1;
    
    return result;
}
