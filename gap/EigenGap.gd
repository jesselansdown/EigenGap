#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#


#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a symmetric real matrix and returns the eigenvalues approximated as floating point values.
#!  Values in matrix can be integers, fractions, or floating point values.
#!  Note that the matrix must be symmetric. This is not checked. A warning is given if the transpose of the
#!  matrix is not equal to the matrix, however this allowed, since the matrix may contain floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealSymmetricMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a real square matrix and returns the eigenvalues approximated as pairs of floating point values,
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a symmetric real matrix and returns the eigenvectors with entries approximated as floating point values.
#!  Values in matrix can be integers, fractions, or floating point values.
#!  Note that the matrix must be symmetric. This is not checked. A warning is given if the transpose of the
#!  matrix is not equal to the matrix, however this allowed, since the matrix may contain floating point values.
DeclareOperation( "ApproximateEigenvectorsOfRealSymmetricMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a real sqyare matrix and returns the eigenvectors with entries approximated as pairs of floating point values, where
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvectorsOfRealMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a real matrix and returns the rank. A tolerance of 10^(-5) is used.
DeclareOperation( "ApproximateRankOfRealMatrix",
	[ IsList ]);
