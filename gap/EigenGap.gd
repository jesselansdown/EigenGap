#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#

DeclareCategory( "IsEigenMatrix", IsObject );


EigenObjectFamily := NewFamily( "EigenObjectFamily" );

BindGlobal("TheTypeEigenMatrix", NewType( EigenObjectFamily, IsEigenMatrix ));

