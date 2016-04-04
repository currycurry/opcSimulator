//
//  currentColor.h
//  opcSimulator
//
//  Created by curry on 3/10/16.
//
//

#ifndef currentColor_h
#define currentColor_h

#include <stdio.h>
#include "ofMain.h"

class currentColor {
    
public:
    
    void setup();
    void update();
    
    //variables
    vector<ofColor> colorPalette;
    ofColor getCurrentColor();
    
    ofColor fromColor;
    ofColor toColor;
    ofColor currentColor;
    int nextColor;
    int lastColor;
    
    float transSpeed; // moves 0 - 1 to transition fromColor toColor
    
    //color timers
    long startTime;
    long currentTime;
    long lastTime;
    long colorTime;
    int colorDuration; //how long each color lasts in ms
    int cycles;
    
    
};

#endif
