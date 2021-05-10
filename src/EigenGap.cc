/*
 * EigenGap: Use the Eigen C++ library within GAP
 */

// Include gmp.h *before* switching to C mode, because GMP detects when
// compiled from C++ and then does some things differently, which would
// cause an error if called from within extern "C". But libsing.h
// (indirectly) includes gmp.h ...
#include <gmp.h>

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
using namespace Eigen;
using namespace std;

#include <complex>

extern "C" {
#include "src/compiled.h"          /* GAP headers                */
}



Obj __ApproximateEigenvaluesOfRealSymmetricMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);
  if ( dimension != LEN_PLIST(ELM_PLIST(mat, 1)))
    ErrorMayQuit( "Error: Must give a square matrix", 0, 0 );


  MatrixXd A = MatrixXd(dimension, dimension);
  int i, j;

  for (i = 0; i < dimension; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = i; j < dimension; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
          A(j, i) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "Error: Matrix may only contain floats.", 0, 0 ); 
    }
  }

  SelfAdjointEigenSolver<MatrixXd> es(A);

  Obj eigenvalues = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(eigenvalues, dimension);
  for (i = 0; i < dimension; i = i+1){
    SET_ELM_PLIST(eigenvalues, i+1, NEW_MACFLOAT(es.eigenvalues().col(0)[i]));
  }

  return eigenvalues;

}


Obj __ApproximateEigenvaluesOfRealMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);
  if ( dimension != LEN_PLIST(ELM_PLIST(mat, 1)))
    ErrorMayQuit( "Error: Must give a square matrix", 0, 0 );


  MatrixXd A = MatrixXd(dimension, dimension);
  int i, j;

  for (i = 0; i < dimension; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < dimension; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "Error: Matrix may only contain floats.", 0, 0 ); 
    }
  }

  EigenSolver<MatrixXd> es(A);

  Obj eigenvalues = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(eigenvalues, dimension);
  for (i = 0; i < dimension; i = i+1){
    Obj complex_value = NEW_PLIST(T_PLIST, 2);
    SET_LEN_PLIST(complex_value, 2);
    SET_ELM_PLIST(complex_value, 1, NEW_MACFLOAT(es.eigenvalues().col(0)[i].real()));
    SET_ELM_PLIST(complex_value, 2, NEW_MACFLOAT(es.eigenvalues().col(0)[i].imag()));
    SET_ELM_PLIST(eigenvalues, i+1, complex_value);
  }

  return eigenvalues;

}



typedef Obj (* GVarFunc)(/*arguments*/);

#define GVAR_FUNC_TABLE_ENTRY(srcfile, name, nparam, params) \
  {#name, nparam, \
   params, \
   (GVarFunc)name, \
   srcfile ":Func" #name }

// Table of functions to export
static StructGVarFunc GVarFuncs [] = {
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenRealMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenComplexMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", ViewEigenMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __SignatureOfComplexHermitianMatrix, 3, "mat, dim, tol"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __SignatureOfRealSymmetricMatrix, 3, "mat, dim, tol"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __SpectrumOfRealMatrix, 2, "mat, dim"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenSolutionMat, 2, "mat, vec"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", ReverseEigenMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenRank, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", Eigensolver, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenComplexMatrixEigenvalues, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenEigenvectors, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvaluesOfRealSymmetricMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvaluesOfRealMatrix, 1, "mat"),

	{ 0 } /* Finish with an empty entry */

};

/******************************************************************************
*F  InitKernel( <module> )  . . . . . . . . initialise kernel data structures
*/
static Int InitKernel( StructInitInfo *module )
{
    /* init filters and functions                                          */
    InitHdlrFuncsFromTable( GVarFuncs );

  
    InitCopyGVar( "TheTypeEigenMatrix", &TheTypeEigenMatrix );


  T_EIGEN = RegisterPackageTNUM("EigenMatrix", EigenTypeFunc);

    InitMarkFuncBags(T_EIGEN, &MarkNoSubBags);
    InitFreeFuncBag(T_EIGEN, &EigenFreeFunc);

    CopyObjFuncs[ T_EIGEN ] = &EigenCopyFunc;
    CleanObjFuncs[ T_EIGEN ] = &EigenCleanFunc;
  IsMutableObjFuncs[ T_EIGEN ] = &EigenIsMutableObjFuncs;



  
    InitCopyGVar( "TheTypeEigenComplexMatrix", &TheTypeEigenComplexMatrix );


  T_EIGENCOMPLEXMATRIX = RegisterPackageTNUM("EigenMatrix", EigenComplexMatrixTypeFunc);

    InitMarkFuncBags(T_EIGENCOMPLEXMATRIX, &MarkNoSubBags);
    InitFreeFuncBag(T_EIGENCOMPLEXMATRIX, &EigenComplexMatrixFreeFunc);

    CopyObjFuncs[ T_EIGENCOMPLEXMATRIX ] = &EigenComplexMatrixCopyFunc;
    CleanObjFuncs[ T_EIGENCOMPLEXMATRIX ] = &EigenCleanFunc;
  IsMutableObjFuncs[ T_EIGENCOMPLEXMATRIX ] = &EigenIsMutableObjFuncs;

    return 0;
}

/******************************************************************************
*F  InitLibrary( <module> ) . . . . . . .  initialise library data structures
*/
static Int InitLibrary( StructInitInfo *module )
{
    /* init filters and functions */
    InitGVarFuncsFromTable( GVarFuncs );

    /* return success                                                      */
    return 0;
}

/******************************************************************************
*F  InitInfopl()  . . . . . . . . . . . . . . . . . table of init functions
*/
static StructInitInfo module = {
 /* type        = */ MODULE_DYNAMIC,
 /* name        = */ "EigenGap",
 /* revision_c  = */ 0,
 /* revision_h  = */ 0,
 /* version     = */ 0,
 /* crc         = */ 0,
 /* initKernel  = */ InitKernel,
 /* initLibrary = */ InitLibrary,
 /* checkInit   = */ 0,
 /* preSave     = */ 0,
 /* postSave    = */ 0,
 /* postRestore = */ 0
};

extern "C"
StructInitInfo *Init__Dynamic( void )
{
    return &module;
}
