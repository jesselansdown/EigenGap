#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#


#! @Chapter Using EigenGAP
#! @Section Spectrums
#! @Arguments RealMatrix
#! @Returns Spectrum
#! @Description
#!	Returns a list of all the eigenvalues (including duplicates), where each eigenvalue is a pair [a, b], denoting a + bi.
DeclareOperation( "ApproximateEigenvaluesOfRealSymmetricMatrix",
	[ IsList ]);

#! @Chapter Using EigenGAP
#! @Section Spectrums
#! @Arguments RealMatrix
#! @Returns Spectrum
#! @Description
#!	Returns a list of all the eigenvalues (including duplicates), where each eigenvalue is a pair [a, b], denoting a + bi.
DeclareOperation( "ApproximateEigenvaluesOfRealMatrix",
	[ IsList ]);
