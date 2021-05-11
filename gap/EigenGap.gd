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
	[ IsMatrixObj ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a real square matrix and returns the eigenvalues approximated as pairs of floating point values,
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealMatrix",
	[ IsMatrixObj ]);

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
	[ IsMatrixObj ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a real sqyare matrix and returns the eigenvectors with entries approximated as pairs of floating point values, where
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvectorsOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns Rank
#! @Description
#!	Takes a real matrix and returns the rank. A tolerance of 10^(-5) is used.
DeclareOperation( "ApproximateRankOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Using EigenGAP
#! @Section Functionality
#! @Arguments M
#! @Returns [Kernel, Image]
#! @Description
#!	Returns the kernel and image of a real matrix M, where vectors are multplied on the right, Mx.
#!  The rows of the kernel correspond to vectors in the kernel, and the rows in the image correspond to vectors in the image.
#!  Entries in the vectors are approximated as floating point values.
DeclareOperation( "ApproximateKernelAndImageOfRealMatrix",
	[ IsMatrixObj ]);
