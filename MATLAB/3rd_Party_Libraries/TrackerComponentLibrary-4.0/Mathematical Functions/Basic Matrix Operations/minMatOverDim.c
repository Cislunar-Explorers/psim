/**MINMATOVERDIM Given a multidimensional matrix C, this function returns
 *          matrix M that is obtained by minimizing C over the given
 *          dimension and removing the given dimension. This is equivalent
 *          to using a call to min(C,[],minIdx) and a reshape command in
 *          Matlab. However, here, we do it without using any matrix/
 *          vector commands so that it can mirror how one might implement
 *          such a function in C. The algorithm is described in the
 *          comments to the Matlab implementation.
 *
 *INPUTS: C A real n1Xn2Xn3..XnS S-dimensional hypermatrix.
 *  minIdx The real index from 1 to S over which the minimization should be
 *         performed.
 *
 *OUTPUTS: M An n1X...n(minIdx-1)Xn(minIdx+1)X...nS matrix holding the
 *          minimum values over the specified dimension.
 *
 *The algorithm can be compiled for use in Matlab  using the 
 * CompileCLibraries function.
 *
 *The algorithm is run in Matlab using the command format
 * M=minMatOverDim(C,minIdx)
 *
 *March 2018 David F. Crouse, Naval Research Laboratory, Washington D.C.
 */
/*(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.*/

#include "mex.h"
/* This header validates inputs and includes a header needed to handle
 * Matlab matrices.*/
#include "MexValidation.h"

#include "basicMatOps.h"

void mexFunction(const int nlhs, mxArray *plhs[], const int nrhs, const mxArray *prhs[]) {
    const size_t *nVals;
    size_t S;
    mxClassID theClassID;
    mxArray *MMATLAB;
    size_t *nValsRet;
    const void *C;
    size_t minIdx;
    
    if(nrhs!=2){
        mexErrMsgTxt("Incorrect number of inputs.");
        return;
    }
    
    if(nlhs>1) {
        mexErrMsgTxt("Invalid number of outputs.");
        return;
    }
    
    if(mxIsComplex(prhs[0])==true) {
        mexErrMsgTxt("C must be real.");
        return;
    }
    
    theClassID=mxGetClassID(prhs[0]);
    
    if(mxIsEmpty(prhs[0])) {
        plhs[0]=mxCreateNumericMatrix(0, 0, mxDOUBLE_CLASS, mxREAL);
        return;
    }
    
    C=mxGetData(prhs[0]);
    nVals=mxGetDimensions(prhs[0]);
    S=mxGetNumberOfDimensions(prhs[0]);
    minIdx=getSizeTFromMatlab(prhs[1]);
    
    if(minIdx<1) {
        mexErrMsgTxt("Invalid value of minIdx given.");
        return;   
    }
    
    //Convert to a C-style index.
    minIdx--;
    
    nValsRet=(size_t*)mxMalloc(S*sizeof(size_t));
    memcpy(nValsRet,nVals,S*sizeof(size_t));
    if(minIdx<S) {
        nValsRet[minIdx]=1;
    }

    switch(theClassID) {
        case mxDOUBLE_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxDOUBLE_CLASS,mxREAL);
            double *M=(double*)mxGetData(MMATLAB);
            minMatOverDimCDouble(S,nVals,M,C,minIdx);
        }
            break;
        case mxSINGLE_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxSINGLE_CLASS,mxREAL);
            float *M=(float*)mxGetData(MMATLAB);
            minMatOverDimCFloat(S,nVals,M,C,minIdx);
        }
            break;
        case mxCHAR_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxCHAR_CLASS,mxREAL);
            char *M=(char*)mxGetData(MMATLAB);
            minMatOverDimCChar(S,nVals,M,C,minIdx);
        }
            break;
        case mxINT8_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxINT8_CLASS,mxREAL);
            int8_t *M=(int8_t*)mxGetData(MMATLAB);
            minMatOverDimCInt8T(S,nVals,M,C,minIdx);
        }
            break;
        case mxUINT8_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxUINT8_CLASS,mxREAL);
            uint8_t *M=(uint8_t*)mxGetData(MMATLAB);
            minMatOverDimCUInt8T(S,nVals,M,C,minIdx);
        }
            break;
        case mxINT16_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxINT16_CLASS,mxREAL);
            int16_t *M=(int16_t*)mxGetData(MMATLAB);
            minMatOverDimCInt16T(S,nVals,M,C,minIdx);
        }
            break;
        case mxUINT16_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxUINT16_CLASS,mxREAL);
            uint16_t *M=(uint16_t*)mxGetData(MMATLAB);
            minMatOverDimCUInt16T(S,nVals,M,C,minIdx);
        }
            break;
        case mxINT32_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxINT32_CLASS,mxREAL);
            int32_t *M=(int32_t*)mxGetData(MMATLAB);
            minMatOverDimCInt32T(S,nVals,M,C,minIdx);
        }
            break;
        case mxUINT32_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxUINT32_CLASS,mxREAL);
            uint32_t *M=(uint32_t*)mxGetData(MMATLAB);
            minMatOverDimCUInt32T(S,nVals,M,C,minIdx);
        }
            break;
        case mxINT64_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxINT64_CLASS,mxREAL);
            int64_t *M=(int64_t*)mxGetData(MMATLAB);
            minMatOverDimCInt64T(S,nVals,M,C,minIdx);
        }
            break;
        case mxUINT64_CLASS:
        {
            MMATLAB=mxCreateNumericArray(S,nValsRet,mxUINT64_CLASS,mxREAL);
            uint64_t *M=(uint64_t*)mxGetData(MMATLAB);
            minMatOverDimCUInt64T(S,nVals,M,C,minIdx);
        }
            break;
        case mxUNKNOWN_CLASS:
        case mxCELL_CLASS:
        case mxSTRUCT_CLASS:
        case mxLOGICAL_CLASS:
        case mxVOID_CLASS:
        case mxFUNCTION_CLASS:
        case mxOPAQUE_CLASS:
        case mxOBJECT_CLASS:
        default:
            mexErrMsgTxt("C is of an unsupported data type.");
            return;   
    }
    
    mxFree(nValsRet);//MMATLAB has a copy.

    plhs[0]=MMATLAB;
}

/*LICENSE:
%
%The source code is in the public domain and not licensed or under
%copyright. The information and software may be used freely by the public.
%As required by 17 U.S.C. 403, third parties producing copyrighted works
%consisting predominantly of the material produced by U.S. government
%agencies must provide notice with such work(s) identifying the U.S.
%Government material incorporated and stating that such material is not
%subject to copyright protection.
%
%Derived works shall not identify themselves in a manner that implies an
%endorsement by or an affiliation with the Naval Research Laboratory.
%
%RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF THE
%SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY THE NAVAL
%RESEARCH LABORATORY FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE ACTIONS
%OF RECIPIENT IN THE USE OF THE SOFTWARE.*/
