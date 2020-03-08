function compile_indirect(flags, common_scs)

%The paths have been modified by David F. Crouse to reflect the folder
%structure for inclusion in the Tracker Component Library, January 2018.

% compile indirect
if (flags.COMPILE_WITH_OPENMP)
    cmd = sprintf('mex -O %s %s %s %s COMPFLAGS="/openmp \\$COMPFLAGS" CFLAGS="\\$CFLAGS -fopenmp" ../linsys/indirect/private.c %s -I.. -I../include %s %s %s -output scs_indirect',  flags.arr, flags.LCFLAG, common_scs, flags.INCS, flags.link, flags.LOCS, flags.BLASLIB, flags.INT);
else
    cmd = sprintf('mex -O %s %s %s %s ../linsys/indirect/private.c %s -I.. -I../include -I../linsys %s %s %s -output scs_indirect',  flags.arr, flags.LCFLAG, common_scs, flags.INCS, flags.link, flags.LOCS, flags.BLASLIB, flags.INT);
end
eval(cmd);
