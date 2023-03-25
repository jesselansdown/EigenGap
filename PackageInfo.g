#
# EigenGap: Use the Eigen C++ library within GAP
#
# This file contains package meta data. For additional information on
# the meaning and correct usage of these fields, please consult the
# manual of the "Example" package as well as the comments in its
# PackageInfo.g file.
#

SetPackageInfo( rec(

PackageName := "EigenGap",
Subtitle := "Use the Eigen C++ library within GAP",
Version := "0.1",
Date := "12/05/2021", # dd/mm/yyyy format

Persons := [
  rec(
    IsAuthor := true,
    IsMaintainer := true,
    FirstNames := "Jesse",
    LastName := "Lansdown",
    WWWHome := "http://www.jesselansdown.com",
    Email := "jesse.lansdown@uwa.edu.au",
    PostalAddress := Concatenation(
               "Jesse Lansdown\n",
               "Centre for the Mathematics of Symmetry and Computation\n",
               "The University of Western Australia\n",
               "35 Stirling Highway\n",
               "PERTH WA 6009\n",
               "Australia" ),
    Place := "Perth",
    Institution := "The University of Western Australia",
  ),
],

#SourceRepository := rec( Type := "TODO", URL := "URL" ),
#IssueTrackerURL := "TODO",
#SupportEmail := "TODO",

PackageWWWHome := "http://TODO/",

PackageInfoURL := Concatenation( ~.PackageWWWHome, "PackageInfo.g" ),
README_URL     := Concatenation( ~.PackageWWWHome, "README.md" ),
ArchiveURL     := Concatenation( ~.PackageWWWHome,
                                 "/", ~.PackageName, "-", ~.Version ),

ArchiveFormats := ".tar.gz",

##  Status information. Currently the following cases are recognized:
##    "accepted"      for successfully refereed packages
##    "submitted"     for packages submitted for the refereeing
##    "deposited"     for packages for which the GAP developers agreed
##                    to distribute them with the core GAP system
##    "dev"           for development versions of packages
##    "other"         for all other packages
##
Status := "dev",

AbstractHTML   :=  "",

PackageDoc := rec(
  BookName  := "EigenGap",
  ArchiveURLSubset := ["doc"],
  HTMLStart := "doc/chap0.html",
  PDFFile   := "doc/manual.pdf",
  SixFile   := "doc/manual.six",
  LongTitle := "Use the Eigen C++ library within GAP",
),

Dependencies := rec(
  GAP := ">= 4.10",
  NeededOtherPackages := [ [ "GAPDoc", ">= 1.5" ] ],
  SuggestedOtherPackages := [ ],
  ExternalConditions := [ ],
),

AvailabilityTest := function()
        return true;
    end,

TestFile := "tst/testall.g",

#Keywords := [ "TODO" ],

AutoDoc := rec(
    TitlePage := rec(
        Copyright := Concatenation("&copyright; 2017 - 2021 Jesse Lansdown<P/>\n\n",
        "TODO - License\n"),
        Abstract := "EigenGap is an interface to the C++ library, Eigen, providing basic linear algebra capabilities to GAP using floating point arithmatic"#,
#        Acknowledgements := "TODO"
    )
),

));


