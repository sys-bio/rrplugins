#pragma hdrstop
#include "rr/rrRoadRunner.h"
#include "rr-libstruct/lsMatrix.h"
#include "telOSSpecifics.h"
#include "telplugins_matrix_api.h"
#include "tel_macros.h"
#include "telplugins_utilities.h"
#include "telplugins_cpp_support.h"
#include "telStringUtils.h"
#include "telTelluriumData.h"

namespace tlpc
{
using rr::RoadRunner;
using namespace std;
using tlp::StringList;
using tlpc::createText;

typedef ls::Matrix<double> Matrix;


double* tlp_cc getDataArray(TELHandle handle)
{
    start_try
        Matrix* matrixH = castHandle< ls::Matrix<double> >(handle, __FILE__);
        return matrixH->getArray();
    catch_ptr_macro
}

int tlp_cc getMatrixNumRows(TELHandle handle)
{
    start_try
        Matrix* matrixH = castHandle< ls::Matrix<double> >(handle, __FILE__);
        return matrixH->RSize();
    catch_int_macro
}

int tlp_cc getMatrixNumCols(TELHandle handle)
{
    start_try
        Matrix* matrixH = castHandle< ls::Matrix<double> >(handle, __FILE__);
        return matrixH->CSize();
    catch_int_macro
}

bool tlp_cc getMatrixElement(TELHandle handle, int row, int col, double* value)
{
    start_try
        Matrix* matrixH = castHandle< ls::Matrix<double> >(handle, __FILE__);
        *value = matrixH->Element(row, col);
        return true;
    catch_bool_macro
}

bool tlp_cc setMatrixElement(TELHandle handle, int row, int col, double value)
{
    start_try
        Matrix* matrix = castHandle< ls::Matrix<double> >(handle, __FUNC__);
        (*matrix)(row, col) =  value;
        return true;
    catch_bool_macro
}

TELHandle tlp_cc createMatrix(int nRows, int nCols, char* colNames)
{
    start_try
        Matrix* data = new Matrix(nRows, nCols);
        gHM.registerHandle(data, typeid(data).name());
        if (colNames)
        {
            string cNames(colNames);
        }
        return data;
    catch_ptr_macro
}

bool tlp_cc freeMatrix(TELHandle handle)
{
    start_try
        Matrix* data = castHandle< Matrix >(handle, __FUNC__);
        delete data;
        return true;
    catch_bool_macro
}

}
