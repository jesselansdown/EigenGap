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
#! @Arguments Hermitian complex matrix[, tolerance]
#! @Returns Signature
#! @Description
#!	Takes a hermitian complex matrix and calculates the signature. Takes an optional tolerance to determine
#!	determine positive and negative eigenvalues. Default tolerance is 0.01.
DeclareOperation( "SignatureOfComplexHermitianMatrix",
	[ IsList ]);

DeclareOperation( "SignatureOfComplexHermitianMatrix",
	[ IsList, IsFloat ]);

DeclareOperation( "SignatureOfComplexHermitianMatrixNC",
	[ IsList ]);

DeclareOperation( "SignatureOfComplexHermitianMatrixNC",
	[ IsList, IsFloat ]);
