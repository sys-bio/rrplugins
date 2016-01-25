#ifndef lmObjectiveFunctionH
#define lmObjectiveFunctionH
//---------------------------------------------------------------------------

void lmObjectiveFunction(
const double *par,       //Parameter vector
int           m_dat,     //Dimension of residue vector
void   *userData,        //User data structure
double       *fvec,      //residue vector..
int          *userBreak  //Non zero value means termination
);

#endif
