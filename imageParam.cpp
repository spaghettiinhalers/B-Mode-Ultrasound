#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    // part 2 task 1
    // appropriately initialize variables
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    // assign 1D element position array
    elementPosition = genElementPosition();
    // assign 2D scanline position array
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    // part 2 task 2
    // release dynamically allocated arrays elementPosition and scanlinePosition
    deletePositionArray();
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    // part 2 task 3
    // dynamically allocate a 1D array
    float *elementPosition;
    elementPosition = new float[numElement];

    // deduce values in array using component variable PITCH
    for (int i=0; i<numElement; i++) {
        elementPosition[i] = ( i - ( (numElement-1.0) /2.0 ) ) * PITCH;
    }

    return elementPosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementPosition)
{
    // part 2 task 4
    // takes desired imaging depth and number of pixels per scanline and creates a dynamically allocated 2D array
    cout << "Enter desired imaging depth: ";
    cin >> desiredDepth;
    cout << "Enter number of pixels of the scanline: ";
    cin >> numPixel;

    
    float2 **scanlinePosition;                      // allocation
    scanlinePosition = new float2*[numScanline];
    for (int i=0; i<=numScanline; i++) {            // calculations
        scanlinePosition[i] = new float2[numPixel];
        for (int j=0; j<numPixel; j++) {
            scanlinePosition[i][j].x = (i-((numScanline-1.0)/2.0))*PITCH;
            scanlinePosition[i][j].y = j*(desiredDepth/(numPixel-1.0));
        }
    }

    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    // part 2 task 5
    // returns x-coordinate of a pixel
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    // part 2 task 6
    // returns y-coordinate of a pixel
    return scanlinePosition[scanline][pixel].y;

}

float imageParam::getElementPosition(int element)
{
    // part 2 task 7
    // returns the position of an element
    return elementPosition[element];
}

// part 2 task 8
// returns appropriate private data components from the class
int imageParam::getNumElement()
{
    return numElement;
}

int imageParam::getNumSample()
{
    return numSample;
}

int imageParam::getNumScanline() 
{
    return numScanline;
}

int imageParam::getNumPixel() 
{
    return numPixel;
}

void imageParam::deletePositionArray()
{
    // part 2 task 9
    // release dynamically allocated memory for arrays scanlinePosition and elementPosition
    for (int i = 0; i<numElement; i++) {
        delete[] scanlinePosition[i];
    }
    delete[] elementPosition;
}