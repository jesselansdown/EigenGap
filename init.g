#
# EigenGap: Use the Eigen C++ library within GAP
#
# Reading the declaration part of the package.
#
_PATH_SO:=Filename(DirectoriesPackagePrograms("EigenGap"), "EigenGap.so");
if _PATH_SO <> fail then
    LoadDynamicModule(_PATH_SO);
fi;
Unbind(_PATH_SO);

ReadPackage( "EigenGap", "gap/EigenGap.gd");
