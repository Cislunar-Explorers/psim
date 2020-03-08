/**ASSIGNALGS3D This is a header for C language functions to solve the
 *              axial operations research 3D assignment problem. The inputs
 *              of the specific functions are described in their
 *              implementation files, which are assign3DC.c and
 *              assign3DLBC.c.
 * 
 *Better understanding of the algorithms can usually be obtained from
 *looking at the Matlab implementations.
 *
 *January 2018 David F. Crouse, Naval Research Laboratory, Washington D.C.
 */
/*(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.*/

#ifndef ASSIGNALGS3D
#define ASSIGNALGS3D

//Defines the size_t and ptrdiff_t types
#include <stddef.h>

#if __STDC_VERSION__>=199901L
#include <stdbool.h>
#else
#ifndef _bool_T
#define false 0
#define true 1
#define bool int
#define _bool_T
#endif
#endif

//If using Microsoft Visual Studio
#ifdef _MSC_VER
#ifndef RESTRICT
//Microsoft does not support the restrict keyword in C, but it does have
//its own version.
#define restrict __restrict
#endif
#endif

//Function prototypes.
size_t assign3DCBufferSize(const size_t *nDims,const int subgradMethod);
ptrdiff_t assign3DC(ptrdiff_t * restrict tuples,double *restrict fStar, double * restrict qStar,double * restrict u,void *tempSpace,const size_t *nDims,double * restrict C,bool maximize,const int subgradMethod,const size_t maxIter,const double AbsTol,const double RelTol,const double param1,const double param2,const size_t param3);

//Bounds
size_t assign3DLBHungarianBufferSize(const size_t *nVals);
double assign3DLBHungarian(const size_t *nVals,const double *COrig, void *tempSpace);
size_t assign3DLBDual0BufferSize(const size_t *nVals);
double assign3DLBDual0(const size_t *nVals,const double *C, void *tempSpace);
double assign3DLBCPierskalla(const size_t *nVals,const double *C);

#endif

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
