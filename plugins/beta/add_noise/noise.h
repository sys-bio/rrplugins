#ifndef noiseH
#define noiseH
//---------------------------------------------------------------------------

namespace addNoise
{

class Noise
{
    private:
        double         mMean;
        double         mSigma;

    public:
                    Noise(double m = 0, double s = 1);
        double      getNoise(double mean, double sigma);
        void        randomize();
};

}
#endif
