#
# EigenGap: Use the Eigen C++ library within GAP
#
# This file is a script which compiles the package manual.
#
if fail = LoadPackage("AutoDoc", "2016.02.16") then
    Error("AutoDoc version 2016.02.16 or newer is required.");
fi;

AutoDoc( rec( scaffold := true, autodoc := true ) );
AutoDoc( rec( maketest := rec( commands := [ "LoadPackage( \"EigenGap\" );"]), scaffold := true, autodoc := rec( files := [ "doc/Intro.autodoc", "src/EigenGap.cc"] ) ) );

PrintTo("PACKAGEVERSION", PackageInfo("EigenGap")[1].Version);
