#pragma once
#include "Vector.h"

class DebugObject
{
public:
    Vector xAxis, yAxis, zAxis;
    bool debugMode = false;

    void toggleDebugMode()
    {
        debugMode = !debugMode;
    }
};
