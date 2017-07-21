#
# EigenGap: Use the Eigen C++ library within GAP
#
# This file runs package tests. It is also referenced in the package
# metadata in PackageInfo.g.
#
LoadPackage( "EigenGap" );

TestDirectory(DirectoriesPackageLibrary( "EigenGap", "tst" ),
  rec(exitGAP := true));

FORCE_QUIT_GAP(1); # if we ever get here, there was an error
