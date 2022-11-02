/*
 * EigenGap: Use the Eigen C++ library within GAP
 */

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
  for (i = 0; i < dimension; i = i+1){
    ASS_LIST(eigenvalues, i+1, NEW_MACFLOAT(es.eigenvalues().col(0)[i]));
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
  for (i = 0; i < dimension; i = i+1){
    Obj complex_value = NEW_PLIST(T_PLIST, 2);
    ASS_LIST(complex_value, 1, NEW_MACFLOAT(es.eigenvalues().col(0)[i].real()));
    ASS_LIST(complex_value, 2, NEW_MACFLOAT(es.eigenvalues().col(0)[i].imag()));
    ASS_LIST(eigenvalues, i+1, complex_value);
  }

  return eigenvalues;

}



Obj __ApproximateEigenvectorsOfRealSymmetricMatrix(Obj self, Obj mat)
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

  Obj eigenvectors = NEW_PLIST(T_PLIST, dimension);
  for (i = 0; i < dimension; i = i+1){

    Obj current_eigenvector = NEW_PLIST(T_PLIST, dimension);
    for (j = 0; j < dimension; j = j+1){
      ASS_LIST(current_eigenvector, j+1, NEW_MACFLOAT(es.eigenvectors().row(j)[i]));
    }
    ASS_LIST(eigenvectors, i+1, current_eigenvector);
  }

  return eigenvectors;

}


Obj __ApproximateEigenvectorsOfRealMatrix(Obj self, Obj mat)
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

    Obj eigenvectors = NEW_PLIST(T_PLIST, dimension);
  for (i = 0; i < dimension; i = i+1){

    Obj current_eigenvector = NEW_PLIST(T_PLIST, dimension);
    for (j = 0; j < dimension; j = j+1){
      Obj complex_value = NEW_PLIST(T_PLIST, 2);
      ASS_LIST(complex_value, 1, NEW_MACFLOAT(es.eigenvectors().row(j)[i].real()));
      ASS_LIST(complex_value, 2, NEW_MACFLOAT(es.eigenvectors().row(j)[i].imag()));
      ASS_LIST(current_eigenvector, j+1, complex_value);
    }
    ASS_LIST(eigenvectors, i+1, current_eigenvector);
  }

  return eigenvectors;

}



Obj __ApproximateRankOfRealMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int nrows = LEN_PLIST(mat);
  int ncols = LEN_PLIST(ELM_PLIST(mat, 1));


  MatrixXd A = MatrixXd(nrows, ncols);
  int i, j;

  for (i = 0; i < nrows; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncols; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "Error: Matrix may only contain floats.", 0, 0 ); 
    }
  }

  ColPivHouseholderQR<MatrixXd> lu_decomp(A);
  lu_decomp.setThreshold(1e-5);
  int rank = lu_decomp.rank();

  return INTOBJ_INT(rank);
}

Obj __ApproximateKernelAndImageOfRealMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int nrows = LEN_PLIST(mat);
  int ncols = LEN_PLIST(ELM_PLIST(mat, 1));


  MatrixXd A = MatrixXd(nrows, ncols);
  int i, j;

  for (i = 0; i < nrows; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncols; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "Error: Matrix may only contain floats.", 0, 0 ); 
    }
  }

  FullPivLU<MatrixXd> lu_decomp(A);

  Obj solution = NEW_PLIST(T_PLIST, 2);

  MatrixXd ker = MatrixXd();
  ker = lu_decomp.kernel();

  MatrixXd im = MatrixXd();
  im = lu_decomp.image(A);

  long kernelcols = ker.cols();
  long imagecols = im.cols();


  Obj kernel = NEW_PLIST(T_PLIST, kernelcols);
  for (i = 0; i < kernelcols; i = i+1){
    Obj current_solution_row = NEW_PLIST(T_PLIST, nrows);
    for (j = 0; j < nrows; j = j+1 ){
      ASS_LIST(current_solution_row, j+1, NEW_MACFLOAT(ker.row(j)[i]));
    }
    ASS_LIST(kernel, i+1, current_solution_row);
  }

  Obj image = NEW_PLIST(T_PLIST, imagecols);
  for (i = 0; i < imagecols; i = i+1){
    Obj current_solution_row = NEW_PLIST(T_PLIST, nrows);
    for (j = 0; j < nrows; j = j+1 ){
      ASS_LIST(current_solution_row, j+1, NEW_MACFLOAT(im.row(j)[i]));
    }
    ASS_LIST(image, i+1, current_solution_row);
  }

  ASS_LIST(solution, 1, kernel);
  ASS_LIST(solution, 2,  image);

  return solution;

}



Obj __ApproximateSolutionMat(Obj self, Obj mat, Obj mat2)
{


  int i, j;
  int nrowsA = LEN_PLIST(mat);
  int ncolsA = LEN_PLIST(ELM_PLIST(mat, 1));


  MatrixXd A = MatrixXd(nrowsA, ncolsA);

  for (i = 0; i < nrowsA; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncolsA; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "A may only contain floats.", 0, 0 ); 
    }
  }

  int nrowsB = LEN_PLIST(mat2);
  int ncolsB = LEN_PLIST(ELM_PLIST(mat2, 1));


  MatrixXd B = MatrixXd(nrowsB, ncolsB);

  for (i = 0; i < nrowsB; i = i+1){
    Obj row = ELM_PLIST(mat2, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncolsB; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          B(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "B may only contain floats.", 0, 0 ); 
    }
  }

  if ( nrowsA != nrowsB )
    ErrorMayQuit( "Error: matrix A and matrix B must have compatible dimensions in the equation Ax = b!", 0, 0 );

  MatrixXd x = MatrixXd();
  x = A.colPivHouseholderQr().solve(B);

  double relative_error = (A*x - B).norm() / B.norm(); // norm() is L2 norm
  cout << "The relative error is:\n" << relative_error << endl;


  long nsolrows = x.rows();
  long nsolcols = x.cols();

  Obj solution = NEW_PLIST(T_PLIST, nsolrows);
  for (i = 0; i < nsolrows; i = i+1){
    Obj current_solution_row = NEW_PLIST(T_PLIST, nsolcols);
    for (j = 0; j < nsolcols; j = j+1 ){
      ASS_LIST(current_solution_row, j+1, NEW_MACFLOAT(x.row(i)[j]));
    }
    ASS_LIST(solution, i+1, current_solution_row);
  }
  return solution;
}


Obj __ApproximateInverseOfRealMatrix(Obj self, Obj mat)
{

  int i, j;
  int nrowsA = LEN_PLIST(mat);
  if ( nrowsA != LEN_PLIST(ELM_PLIST(mat, 1)) )
    ErrorMayQuit( "Error: Must give a square matrix", 0, 0 );

  MatrixXd A = MatrixXd(nrowsA, nrowsA);

  for (i = 0; i < nrowsA; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < nrowsA; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_MACFLOAT(entry_ij) ){
          A(i, j) = VAL_MACFLOAT(entry_ij);
        }
        else
          ErrorMayQuit( "A may only contain floats.", 0, 0 ); 
    }
  }


  MatrixXd x = MatrixXd();
  x = A.inverse();


  Obj solution = NEW_PLIST(T_PLIST, nrowsA);
  for (i = 0; i < nrowsA; i = i+1){
    Obj current_solution_row = NEW_PLIST(T_PLIST, nrowsA);
    for (j = 0; j < nrowsA; j = j+1 ){
      ASS_LIST(current_solution_row, j+1, NEW_MACFLOAT(x.row(i)[j]));
    }
    ASS_LIST(solution, i+1, current_solution_row);
  }
  return solution;
}


typedef Obj (* GVarFunc)(/*arguments*/);

#define GVAR_FUNC_TABLE_ENTRY(srcfile, name, nparam, params) \
  {#name, nparam, \
   params, \
   (GVarFunc)name, \
   srcfile ":Func" #name }

// Table of functions to export
static StructGVarFunc GVarFuncs [] = {
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvaluesOfRealSymmetricMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvaluesOfRealMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvectorsOfRealSymmetricMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateEigenvectorsOfRealMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateRankOfRealMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateKernelAndImageOfRealMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateSolutionMat, 2, "mat, mat2"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", __ApproximateInverseOfRealMatrix, 1, "mat"),
	{ 0 } /* Finish with an empty entry */

};

/******************************************************************************
*F  InitKernel( <module> )  . . . . . . . . initialise kernel data structures
*/
static Int InitKernel( StructInitInfo *module )
{
    /* init filters and functions                                          */
    InitHdlrFuncsFromTable( GVarFuncs );

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
