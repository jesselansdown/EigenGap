#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#


#! @Chapter Functionality
#! @Section Eigenvalues
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a symmetric real matrix and returns the eigenvalues approximated as floating point values.
#!  Values in matrix can be integers, fractions, or floating point values.
#!  Note that the matrix must be symmetric. This is not checked. A warning is given if the transpose of the
#!  matrix is not equal to the matrix, however this allowed, since the matrix may contain floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealSymmetricMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Eigenvalues
#! @Arguments M
#! @Returns Eigenvalues
#! @Description
#!	Takes a real square matrix and returns the eigenvalues approximated as pairs of floating point values,
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvaluesOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Eigenvectors
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a symmetric real matrix and returns the (left) eigenvectors with entries approximated as floating point values.
#!  Values in matrix can be integers, fractions, or floating point values.
#!  Note that the matrix must be symmetric. This is not checked. A warning is given if the transpose of the
#!  matrix is not equal to the matrix, however this allowed, since the matrix may contain floating point values.
DeclareOperation( "ApproximateEigenvectorsOfRealSymmetricMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Eigenvectors
#! @Arguments M
#! @Returns Eigenvectors
#! @Description
#!	Takes a real sqyare matrix and returns the (left) eigenvectors with entries approximated as pairs of floating point values, where
#!  where each pair [a, b] represents a complex number of the form a + bi.
#!  Values in matrix can be integers, fractions, or floating point values.
DeclareOperation( "ApproximateEigenvectorsOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Other matrix properties
#! @Arguments M
#! @Returns Rank
#! @Description
#!	Takes a real matrix and returns the rank. A tolerance of 10^(-5) is used.
DeclareOperation( "ApproximateRankOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Other matrix properties
#! @Arguments M
#! @Returns [Kernel, Image]
#! @Description
#!	Returns the (left) kernel and image of a real matrix M.
#!  The rows of the kernel correspond to vectors in the kernel, and the rows in the image correspond to vectors in the image.
#!  Entries in the vectors are approximated as floating point values.
DeclareOperation( "ApproximateKernelAndImageOfRealMatrix",
	[ IsMatrixObj ]);

#! @Chapter Functionality
#! @Section Solving equations
#! @Arguments A, B
#! @Returns X
#! @Description
#!  Given real matrices A and B, solves for XA = B where X is approximated with floating point entries.
#!  If B is a vector (given as a list, rather than a matrix) then ApproximateSolutionMat behaves the same way as SolutionMat.
DeclareOperation( "ApproximateSolutionMat",
	[ IsMatrixObj , IsMatrixObj]);

#! @Chapter Functionality
#! @Section Helper functions
#! @Arguments x, y, epsilon
#! @Returns true or false
#! @Description
#!  Given two floating point values x and y, returns true if x is within epsilon of y and false
#!  otherwise, for some floating point value epsilon.
DeclareOperation( "WithinEpsilon",
	[ IsFloat , IsFloat, IsFloat]);