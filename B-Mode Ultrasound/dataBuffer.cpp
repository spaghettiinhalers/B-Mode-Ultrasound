#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // part 1 task 1
    // initialize variables to 0 and NULL appropriately
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // part 1 task 2
    // assign values to variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    // dynamically allocate a 2D complex array, then populate the array
    dataMatrix = createDataMatrix();
    loadRFData(dataMatrix, imagFile, realFile);
} 

dataBuffer::~dataBuffer()
{
    // part 1 task 3
    // releases 2D array allocated by createDataMatrix()
    deleteDataMatrix();
}

complex **dataBuffer::createDataMatrix()
{
    // part 1 task 4
    // dynamically allocates a 2D complex numElement x numSample array
    complex **RFData;
    RFData = new complex*[numElement];
    for (int i=0; i<numElement; i++) {
        RFData[i] = new complex[numSample];
    }
    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    // part 1 task 5
    // populates 2D complex array dataMatrix
    for (int i = 0; i < numElement; i++)
    {
        for (int j = 0; j < numSample; j++)
        {
            char real[100];
            char imag[100];
            (*realFile).getline(real, 100); // reads from file
            (*imagFile).getline(imag, 100);
            RFData[i][j].real = atof(real); // converts numbers into float values for array
            RFData[i][j].imag = atof(imag);
        }
    }
    return 0;

}

float dataBuffer::getRealRFData(int element,int sample)
{
    // part 1 task 6
    // returns real part of complex data in dataMatrix
    return dataMatrix[element][sample].real;
}
float dataBuffer::getImagRFData(int element,int sample)
{
    // part 1 task 7
    // returns imaginary part of complex data in dataMatrix
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    // part 1 task 8
    // releases dataMatrix
    for (int i = 0; i<numElement; i++) {
        delete[] dataMatrix[i];
    }
    delete[] dataMatrix;
}




