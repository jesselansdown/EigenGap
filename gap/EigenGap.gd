#
# EigenGap: Use the Eigen C++ library within GAP
#
# Declarations
#

DeclareCategory( "IsEigenMatrix", IsObject );


EigenObjectFamily := NewFamily( "EigenObjectFamily" );

BindGlobal("TheTypeEigenMatrix", NewType( EigenObjectFamily, IsEigenMatrix ));


DeclareCategory( "IsEigenTypeVector", IsObject );

BindGlobal("TheTypeEigenTypeVector", NewType( EigenObjectFamily, IsEigenTypeVector ));

