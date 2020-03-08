function W=twoMatDiagSVD(C1,C2)
%%TWOMATDIAGSVD Given two real or complex Hermitian matrices, the first of
%               which must be positive definite, find a matrix W that
%               diagonalizes both of them. Specifically, W*C1*W'=I and
%               W*C2*W'=a diagonal matrix. The technique described in [1]
%               using singular value decomposition is used.
%
%INPUTS: C1 An NXN real or complex positive definite Hermitian matrix.
%        C2 An NXN real or complex Hermitian matrix. This matrix does not
%           have to be positive definite.
%
%OUTPUTS: W An NXN matrix such that W*C1*W'=identity matrix and W*C2*W'=a
%           diagonal matrix.
%
%Joint diagonalization of az pair of matrices arises in the fusion problem
%discussed in [1], among other applications. If both matrices are not
%positive definite, then the jointMatDiagFrob function can produce the
%desired W diagonalization matrix.
%
%EXAMPLE 1:
%Here, we diagonalize two real, positive definite matrices:
% C1=[87, 25, 18, 31;
%     25, 63, 20, 17;
%     18, 20, 65, 29;
%     31, 17, 29, 65];
% C2=[57,  7, 12, 17;
%      7, 47, 17, 22;
%     12, 17, 37, 27;
%     17, 22, 27, 27];
% %C1 is positive definite. C2 is positive semi-definite.
% W=twoMatDiagSVD(C1,C2);
% offDiagErr1=W*C1*W'-diag(diag(W*C1*W'))
% offDiagErr2=W*C2*W'-diag(diag(W*C2*W'))
%One will see that the off-diagonal errors are on the order of 1e-16, which
%is around what one would expect with finite precision limitiations.
%
%EXAMPLE 2:
%This is the diagonalization of two complex Hermitian matrices, the first
%of which is positive definite and the second of which has some negative
%eigenvalues.
%C1 is positive definite.
% C1=[  9+  0*1i,   -65+  0*1i,  -11-153*1i,  -91-173*1i;
%     -65+  0*1i,    83+  0*1i,   54- 38*1i,   31+ 28*1i;
%     -11+153*1i,    54+ 38*1i,  130+  0*1i,   16- 47*1i;
%     -91+173*1i,    31- 28*1i,   16+ 47*1i,   22+  0*1i]+215*eye(4);
% %C2 has both positive and negative eigenvalues.
% C2=[-16+  0*1i,  -32- 56*1i,  -12-128*1i,   16+114*1i;
%     -32+ 56*1i,   79+  0*1i,  -87- 67*1i,  -48+ 51*1i;
%     -12+128*1i,  -87+ 67*1i,   76+  0*1i,   -7- 96*1i;
%      16-114*1i,  -48- 51*1i,   -7+ 96*1i, -147+  0*1i];
% W=twoMatDiagSVD(C1,C2);
% offDiagErr=W*C1*W'-diag(diag(W*C1*W'))
% offDiagErr=W*C2*W'-diag(diag(W*C2*W'))
%One will see that the errors are on the order of 1e-14 or less, which is
%around what one would expect with finite precision errors.
%
%REFERENCES:
%[1] J. Nyg�rds, V. Deleskog, and G. Hendeby, "Safe fusion compared to
%    established distributed fusion methods," in IEEE International
%    Conference on Multisensor Fusion and Integration for Intelligent
%    Systems, Baden-Baden, Germany, 19-21 Sep. 2016, pp. 265-271.
%
%July 2018 David F. Crouse, Naval Research Laboratory, Washington D.C.
%(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.

%Note that C1=U1*D1*U1' for a valid covariance matrix.
[U1,D1]=svd(C1);%Equation 6
d1=diag(D1);

D1Root=diag(1./sqrt(d1));

temp=D1Root*U1';
[U2,~]=svd(temp*C2*temp');%Equation 7.

W=U2'*D1Root*U1';%Equation 8a
%Note that W*C1*W'=eye(xDim,xDim);

end

%LICENSE:
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
%OF RECIPIENT IN THE USE OF THE SOFTWARE.
