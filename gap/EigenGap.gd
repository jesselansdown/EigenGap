#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#

DeclareCategory( "IsEigenMatrix", IsObject );


EigenObjectFamily := NewFamily( "EigenObjectFamily" );

BindGlobal("TheTypeEigenMatrix", NewType( EigenObjectFamily, IsEigenMatrix ));


DeclareCategory( "IsEigenComplexMatrix", IsObject );

BindGlobal("TheTypeEigenComplexMatrix", NewType( EigenObjectFamily, IsEigenComplexMatrix ));






#! @Chapter Using EigenGAP
#! @Section Signatures
#! @Arguments RealSymmetricMatrix[, tolerance]
#! @Returns Signature
#! @Description
#!	Takes a real symmetric matrix and calculates the signature = (n_+, n_0, n_-). Takes an optional tolerance to determine
#!	determine positive and negative eigenvalues. Default tolerance is 0.01.
DeclareOperation( "SignatureOfRealSymmetricMatrix",
	[ IsList ]);

DeclareOperation( "SignatureOfRealSymmetricMatrix",
	[ IsList, IsFloat ]);

#! @Chapter Using EigenGAP
#! @Section Signatures
#! @Arguments RealSymmetricMatrix[, tolerance]
#! @Returns Signature
#! @Description
#!	Same as 'SignatureOfRealSymmetricMatrix' but without checking that the matrix is a real symmetric matrix.
DeclareOperation( "SignatureOfRealSymmetricMatrixNC",
	[ IsList ]);

DeclareOperation( "SignatureOfRealSymmetricMatrixNC",
	[ IsList, IsFloat ]);





#! @Chapter Using EigenGAP
#! @Section Signatures
#! @Arguments HermitianComplexMatrix[, tolerance]
#! @Returns Signature
#! @Description
#!	Takes a hermitian complex matrix and calculates the signature = (n_+, n_0, n_-). Takes an optional tolerance to determine
#!	determine positive and negative eigenvalues. Default tolerance is 0.01.
DeclareOperation( "SignatureOfComplexHermitianMatrix",
	[ IsList ]);

DeclareOperation( "SignatureOfComplexHermitianMatrix",
	[ IsList, IsFloat ]);

#! @Chapter Using EigenGAP
#! @Section Signatures
#! @Arguments HermitianComplexMatrix[, tolerance]
#! @Returns Signature
#! @Description
#!	Same as 'SignatureOfComplexHermitianMatrix' but without checking that the matrix is a hermitian complex matrix.
DeclareOperation( "SignatureOfComplexHermitianMatrixNC",
	[ IsList ]);

DeclareOperation( "SignatureOfComplexHermitianMatrixNC",
	[ IsList, IsFloat ]);


#! @Chapter Using EigenGAP
#! @Section Spectrums
#! @Arguments RealMatrix
#! @Returns Spectrum
#! @Description
#!	Returns a list of all the eigenvalues (including duplicates), where each eigenvalue is a pair [a, b], denoting a + bi.
DeclareOperation( "SpectrumOfRealMatrix",
	[ IsList ]);
