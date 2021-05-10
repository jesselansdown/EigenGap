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




Obj TheTypeEigenMatrix;

void SET_EIGENMATRIX(Obj o, MatrixXd* p) {
    ADDR_OBJ(o)[0] = (Obj)p;
}

MatrixXd* GET_EIGENMATRIX(Obj o) {
    return (MatrixXd*)(ADDR_OBJ(o)[0]);
}

#define IS_EIGENMATRIX(o) (TNUM_OBJ(o) == T_EIGEN)

UInt T_EIGEN = 0;

Obj NewEigenMatrix(MatrixXd* C)
{
    Obj o;
    o = NewBag(T_EIGEN, 1 * sizeof(Obj));
    SET_EIGENMATRIX(o, C);
    return o;
}

/* Free function */
void EigenFreeFunc(Obj o)
{
  delete GET_EIGENMATRIX(o);
}

/* Type object function for the object */
Obj EigenTypeFunc(Obj o)
{
    return TheTypeEigenMatrix;
}

Obj EigenCopyFunc(Obj o, Int mut)
{
  MatrixXd* B = new MatrixXd(*GET_EIGENMATRIX(o));
  return NewEigenMatrix(B);
}

void EigenCleanFunc(Obj o)
{
}

Int EigenIsMutableObjFuncs(Obj o)
{
    return 0L;
}




Obj TheTypeEigenComplexMatrix;

void SET_EIGENCOMPLEXMATRIX(Obj o, MatrixXcd* p) {
    ADDR_OBJ(o)[0] = (Obj)p;
}

MatrixXcd* GET_EIGENCOMPLEXMATRIX(Obj o) {
    return (MatrixXcd*)(ADDR_OBJ(o)[0]);
}

#define IS_EIGENCOMPLEXMATRIX(o) (TNUM_OBJ(o) == T_EIGENCOMPLEXMATRIX)

UInt T_EIGENCOMPLEXMATRIX = 0;

Obj NewEigenComplexMatrix(MatrixXcd* C)
{
    Obj o;
    o = NewBag(T_EIGENCOMPLEXMATRIX, 1 * sizeof(Obj));
    SET_EIGENCOMPLEXMATRIX(o, C);
    return o;
}

/* Free function */
void EigenComplexMatrixFreeFunc(Obj o)
{
  delete GET_EIGENCOMPLEXMATRIX(o);
}

/* Type object function for the object */
Obj EigenComplexMatrixTypeFunc(Obj o)
{
    return TheTypeEigenComplexMatrix;
}

Obj EigenComplexMatrixCopyFunc(Obj o, Int mut)
{
  MatrixXcd* V = new MatrixXcd(*GET_EIGENCOMPLEXMATRIX(o));
  return NewEigenComplexMatrix(V);
}


/*******************************************
Setting up the matrices
********************************************/

/*
  #! @Chapter Using EigenGAP
  #! @Section Converting Matrices
  #! @Arguments Matrix
  #! @Returns EigenRealMatrix object
  #! @Description
  #!  Takes a matrix with real entries and converts it to an Eigen type matrix.
  #!  Note that the entries must be either integers or floats. Fractional entries will
  #!  not be accepted, and must first be converted to a float.
  DeclareGlobalFunction("EigenRealMatrix");
*/

Obj EigenRealMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int nrows = LEN_PLIST(mat);
  int ncols = LEN_PLIST(ELM_PLIST(mat, 1));


  MatrixXd* A = new MatrixXd(nrows, ncols);
  int i, j;

  for (i = 0; i < nrows; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncols; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_INTOBJ(entry_ij) )
          (*A)(i, j) = INT_INTOBJ(entry_ij);
        else if ( IS_MACFLOAT(entry_ij) )
          (*A)(i, j) = VAL_MACFLOAT(entry_ij);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 
    }
  }

  return NewEigenMatrix(A);

}



/*
  #! @Chapter Using EigenGAP
  #! @Section Converting Matrices
  #! @Arguments Matrix
  #! @Returns EigenComplexMatrix object
  #! @Description
  #!  Takes a matrix with complex entries and converts it to an Eigen type matrix. The entries
  #!  must be a list [a, b] where a and b are either integers or floats.
  DeclareGlobalFunction("EigenComplexMatrix");
*/


Obj EigenComplexMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  if ( ! IS_PLIST(ELM_PLIST(mat, 1)))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int nrows = LEN_PLIST(mat);
  int ncols = LEN_PLIST(ELM_PLIST(mat, 1));


  MatrixXcd* A = new MatrixXcd(nrows, ncols);
  int i, j;

  for (i = 0; i < nrows; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < ncols; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
      if ( ! IS_PLIST(entry_ij) )
        ErrorMayQuit( "Error: Must give a complex_value", 0, 0 );
        Obj rl = ELM_PLIST(entry_ij, 1);
        Obj cmplx = ELM_PLIST(entry_ij, 2);

        complex<double> value(1.0, 2.0);
        double rl2;
        if ( IS_MACFLOAT(rl) )
          rl2 = VAL_MACFLOAT(rl);
        else if ( IS_INTOBJ(rl) )
          rl2 = INT_INTOBJ(rl);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 
 
        double cmplx2;
        if ( IS_MACFLOAT(cmplx) )
          cmplx2 = VAL_MACFLOAT(cmplx);
        else if ( IS_INTOBJ(cmplx) )
          cmplx2 = INT_INTOBJ(cmplx);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 

        value = std::complex<double>(rl2, cmplx2);
        (*A)(i, j) = value;

    }
  }

  return NewEigenComplexMatrix(A);

}



/*
  #! @Chapter Using EigenGAP
  #! @Section Converting Matrices
  #! @Arguments EigenRealMatrix/EigenComplexMatrix
  #! @Returns True
  #! @Description
  #! Takes an Eigen real or complex matrix object and prints it to the screen.
  DeclareGlobalFunction("ViewEigenMatrix");
*/


Obj ViewEigenMatrix(Obj self, Obj mat)
{
  if ( IS_EIGENMATRIX(mat)){
    MatrixXd *A = GET_EIGENMATRIX(mat);
    cout << "Here is the matrix you entered:" << endl << *A << endl << endl;
  }
  else if ( IS_EIGENCOMPLEXMATRIX(mat)){

    MatrixXcd *A = GET_EIGENCOMPLEXMATRIX(mat);
   cout << "Here is the matrix you entered:" << endl << *A << endl << endl;
  }
  else{
      ErrorMayQuit( "Error: Must pass an Eigen real or complex matrix object.", 0, 0 ); 
  }
  return True;
}





/*******************************************
Signatures
********************************************/


Obj __SignatureOfComplexHermitianMatrix(Obj self, Obj mat, Obj dim, Obj tol)
{

  if (! IS_EIGENCOMPLEXMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXcd *A = GET_EIGENCOMPLEXMATRIX(mat);
  ComplexEigenSolver<MatrixXcd> es(*A);

  int dimension = INT_INTOBJ(dim);
  int i, j;

  Obj eigenvalues = NEW_PLIST(T_PLIST, 3);

  int n0 =0;
  int nplus = 0;
  int nminus =0;
  double tol2 = VAL_MACFLOAT(tol);

  for (i = 0; i < dimension; i = i+1){
    if (es.eigenvalues().col(0)[i].real() > tol2)
    {
      nplus = nplus +1 ;
    }
    else if (es.eigenvalues().col(0)[i].real() < -1*tol2)
    {
      nminus = nminus +1;
    }
    else
    {
      n0 = n0 +1;
    }
  }

  SET_LEN_PLIST(eigenvalues, 3);
  SET_ELM_PLIST(eigenvalues, 1, INTOBJ_INT(nplus));
  SET_ELM_PLIST(eigenvalues, 2, INTOBJ_INT(n0));
  SET_ELM_PLIST(eigenvalues, 3, INTOBJ_INT(nminus));
  return eigenvalues;

}


Obj __SignatureOfRealSymmetricMatrix(Obj self, Obj mat, Obj dim, Obj tol)
{

  if (! IS_EIGENMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXd *A = GET_EIGENMATRIX(mat);

  int dimension = INT_INTOBJ(dim);
  int i, j;

  EigenSolver<MatrixXd> es(*A);

  double val;
  int pos = 0;
  int neg = 0;
  int null = 0;
  double tol2 = VAL_MACFLOAT(tol);

  for (i = 0; i < dimension; i = i+1){
    val = es.eigenvalues().col(0)[i].real();
    if (val > tol2)
      pos = pos + 1;
    else if (val < -1*tol2)
      neg = neg+1;
    else
      null = null + 1;
  }

  Obj signature = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(signature, 3);
  SET_ELM_PLIST(signature, 1, INTOBJ_INT(pos));
  SET_ELM_PLIST(signature, 2, INTOBJ_INT(null));
  SET_ELM_PLIST(signature, 3, INTOBJ_INT(neg));

  return signature;

}



Obj __SpectrumOfRealMatrix(Obj self, Obj mat, Obj dim)
{

  if ( !IS_INTOBJ(dim) )
         ErrorMayQuit( "Error: Must give an Eigen pas the dimension of the matrix", 0, 0 );

  if (! IS_EIGENMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXd *A = GET_EIGENMATRIX(mat);
  EigenSolver<MatrixXd> es(*A);

  long dimension = INT_INTOBJ(dim);
  int i;

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



























/*
  #! @Chapter Using EigenGap
  #! @Section Currently one section
  #! @Arguments the args
  #! @Returns
  #! @Description
  #!  To do.
  DeclareGlobalFunction("GurobiSetIntegerParameter");
*/

// Solves Ax = b for matrix A and vector b

Obj EigenSolutionMat(Obj self, Obj mat, Obj mat2)
{

  if ( ! IS_EIGENMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  if ( ! IS_EIGENMATRIX(mat2))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );


  MatrixXd *A = GET_EIGENMATRIX(mat);
  MatrixXd *V = GET_EIGENMATRIX(mat2);

  int nmatrows = (*A).rows();
  int nvecrows = (*V).rows();
  if ( nmatrows != nvecrows )
    ErrorMayQuit( "Error: matrix A and matrix b must have compatible dimensions in the equation Ax = b!", 0, 0 );

  MatrixXd* x = new MatrixXd();

  (*x) = (*A).colPivHouseholderQr().solve(*V);

  return NewEigenMatrix(x);

}








Obj ReverseEigenMatrix(Obj self, Obj mat)
{

  if ( ! IS_EIGENMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXd *x = GET_EIGENMATRIX(mat);
  long nsolrows = (*x).rows();
  long nsolcols = (*x).cols();

  int i, j;

  Obj solution = NEW_PLIST(T_PLIST, nsolrows);
  SET_LEN_PLIST(solution, nsolrows);
  for (i = 0; i < nsolrows; i = i+1){
    Obj current_solution_row = NEW_PLIST(T_PLIST, nsolcols);
    SET_LEN_PLIST(current_solution_row, nsolcols);
    for (j = 0; j < nsolcols; j = j+1 ){
      SET_ELM_PLIST(current_solution_row, j+1, NEW_MACFLOAT((*x).row(i)[j]));
    }
    SET_ELM_PLIST(solution, i+1, current_solution_row);
  }
  return solution;
}



// rank, kernel, image
Obj EigenRank(Obj self, Obj mat)
{

  if ( ! IS_EIGENMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXd *A = GET_EIGENMATRIX(mat);

  int nmatrows = (*A).rows();

  FullPivLU<MatrixXd> lu_decomp(*A);

  int rank = lu_decomp.rank();

  MatrixXd* x = new MatrixXd();
  (*x) = lu_decomp.kernel();

  MatrixXd* y = new MatrixXd();
  (*y) = lu_decomp.image(*A);

  Obj solution = NEW_PLIST(T_PLIST, 3);
  SET_LEN_PLIST(solution, 3);
  SET_ELM_PLIST(solution, 1, INTOBJ_INT(rank));
  SET_ELM_PLIST(solution, 2, NewEigenMatrix(x));
  SET_ELM_PLIST(solution, 3,  NewEigenMatrix(y));

  return solution;
}


Obj EigenComplexMatrixEigenvalues(Obj self, Obj mat)
{

  if (! IS_EIGENCOMPLEXMATRIX(mat))
          ErrorMayQuit( "Error: Must give an Eigen type matrix", 0, 0 );

  MatrixXcd *A = GET_EIGENCOMPLEXMATRIX(mat);
  ComplexEigenSolver<MatrixXcd> es(*A);

  long dimension = 2;
  int i, j;

//  cout << "Here is the matrix you entered:" << endl << A << endl << endl;

//  cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
//  cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

  cout << es.eigenvalues();
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




// ###################################################







/*
  #! @Chapter Using EigenGap
  #! @Section Currently one section
  #! @Arguments the args
  #! @Returns
  #! @Description
  #!  To do.
  DeclareGlobalFunction("GurobiSetIntegerParameter");
*/

Obj Eigensolver(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  long dimension = LEN_PLIST(mat);

  MatrixXd A(dimension, dimension);
  int i, j;

  for (i = 0; i < dimension; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < dimension; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_INTOBJ(entry_ij) )
          A(j, i) = INT_INTOBJ(entry_ij);
        else if ( IS_MACFLOAT(entry_ij) )
          A(j, i) = VAL_MACFLOAT(entry_ij);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 
    }
  }

//  cout << "Here is the matrix you entered:" << endl << A << endl << endl;

  EigenSolver<MatrixXd> es(A);
//  cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
//  cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

  Obj eigenvectors = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(eigenvectors, dimension);
  for (i = 0; i < dimension; i = i+1){

    Obj current_eigenvector = NEW_PLIST(T_PLIST, dimension);
    SET_LEN_PLIST(current_eigenvector, dimension);
    for (j = 0; j < dimension; j = j+1){
      Obj complex_value = NEW_PLIST(T_PLIST, 2);
      SET_LEN_PLIST(complex_value, 2);
      SET_ELM_PLIST(complex_value, 1, NEW_MACFLOAT(es.eigenvectors().row(j)[i].real()));
      SET_ELM_PLIST(complex_value, 2, NEW_MACFLOAT(es.eigenvectors().row(j)[i].imag()));
      SET_ELM_PLIST(current_eigenvector, j+1, complex_value);
    }
    SET_ELM_PLIST(eigenvectors, i+1, current_eigenvector);
  }


  Obj eigenvalues = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(eigenvalues, dimension);
  for (i = 0; i < dimension; i = i+1){
    Obj complex_value = NEW_PLIST(T_PLIST, 2);
    SET_LEN_PLIST(complex_value, 2);
    SET_ELM_PLIST(complex_value, 1, NEW_MACFLOAT(es.eigenvalues().col(0)[i].real()));
    SET_ELM_PLIST(complex_value, 2, NEW_MACFLOAT(es.eigenvalues().col(0)[i].imag()));
    SET_ELM_PLIST(eigenvalues, i+1, complex_value);
  }


  Obj solution = NEW_PLIST(T_PLIST, 2);
  SET_LEN_PLIST(solution, 2);
  SET_ELM_PLIST(solution, 1, eigenvalues);
  SET_ELM_PLIST(solution, 2, eigenvectors);

  return solution;

}



Obj EigenEigenvectors(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  long dimension = LEN_PLIST(mat);

  MatrixXd A(dimension, dimension);
  int i, j;

  for (i = 0; i < dimension; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < dimension; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_INTOBJ(entry_ij) )
          A(j, i) = INT_INTOBJ(entry_ij);
        else if ( IS_MACFLOAT(entry_ij) )
          A(j, i) = VAL_MACFLOAT(entry_ij);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 
    }
  }

//  cout << "Here is the matrix you entered:" << endl << A << endl << endl;

  EigenSolver<MatrixXd> es(A);
//  cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
//  cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

  Obj eigenvectors = NEW_PLIST(T_PLIST, dimension);
  SET_LEN_PLIST(eigenvectors, dimension);
  for (i = 0; i < dimension; i = i+1){

    Obj current_eigenvector = NEW_PLIST(T_PLIST, dimension);
    SET_LEN_PLIST(current_eigenvector, dimension);
    for (j = 0; j < dimension; j = j+1){
      Obj complex_value = NEW_PLIST(T_PLIST, 2);
      SET_LEN_PLIST(complex_value, 2);
      SET_ELM_PLIST(complex_value, 1, NEW_MACFLOAT(es.eigenvectors().row(j)[i].real()));
      SET_ELM_PLIST(complex_value, 2, NEW_MACFLOAT(es.eigenvectors().row(j)[i].imag()));
      SET_ELM_PLIST(current_eigenvector, j+1, complex_value);
    }
    SET_ELM_PLIST(eigenvectors, i+1, current_eigenvector);
  }


  return eigenvectors;

}




// New stuff


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
