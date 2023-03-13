#include "BmodeClass.h"

using namespace std;
BmodeClass::BmodeClass()
{
    // part 3 task 1
    // set variables to 0 or NULL appropriately
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    // part 3 task 2
    imparams = params;
    RFData = data;
    line = numline;

    // allocate memory for scanline
    scanline = createScanline(imparams->getNumPixel());
    // creates scanline
    beamform();
}

BmodeClass::~BmodeClass()
{
    // part 3 task 3
    // releases arrays dynamically allocated for scanline
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    // part 3 task 4
    // dynamically allocates a 1D float numPixel size array
    float *mem;
    mem = new float[numPixel];
    return mem;
}

void BmodeClass::beamform()
{
    // part 3 task 5
    // assign values to variables from private data components
    int numPixel = imparams->getNumPixel();
    int numElement = imparams->getNumElement();
    int SOS = imparams->SOS;
    int numScanline = imparams->getNumScanline();
    int pixel = imparams->getNumPixel();
    int FS = imparams->FS;
    int numSample = imparams->getNumSample();

    // creates new variables for calculation process
    float t_back;
    float t_for;
    float t_tot;
    int **s;
    s = new int*[numPixel];
    for (int i=0; i<numPixel; i++) {
        s[i] = new int[numElement];
    }
    float *Preal;
    Preal = new float[numPixel];
    float *Pimag;
    Pimag = new float[numPixel];

    // perform necessary calculations to obtain final echo magnitude for ith scanline location
    for (int i=0; i<numPixel; i++) {
        Preal[i] = 0;
        Pimag[i] = 0;
        for (int j=0; j<numElement; j++) {
            t_back = sqrt(pow(imparams->getYPosition(line, i),2) + pow(imparams->getXPosition(line, i) - imparams->getElementPosition(j),2))/SOS;
            t_for = (imparams->getYPosition(line, i))/SOS;
            t_tot = t_back + t_for;

            s[i][j] = floor(t_tot*FS);
            if (s[i][j]<numSample) {
                Preal[i] += RFData->getRealRFData(j,s[i][j]);
                Pimag[i] += RFData->getImagRFData(j,s[i][j]);
            }
        }
        scanline[i] = sqrt( pow(Preal[i], 2) + pow(Pimag[i], 2) );
    }
    return;
}

void BmodeClass::getScanline(float *data)
{
    // part 3 task 6
    // copies all content from scanline to data array
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    // part 3 task 7
    // releases memory allocated for scanline
    delete[] scanline;
}
