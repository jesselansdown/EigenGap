#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#


#! @Chapter Using EigenGAP
#! @Section Eigenvalues
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a symmetric real matrix and returns the eigenvalues approximated as floating point values.
#!  Note that the matrix must be symmetric. This is not checked, however.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealSymmetricMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Eigenvalues
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a real matrix and returns the eigenvalues approximated as floating point values.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealMatrix",
	[ IsList ]);
