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




Obj EigenMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);

  MatrixXd* A = new MatrixXd(dimension, dimension);
  int i, j;

  for (i = 0; i < dimension; i = i+1){
    Obj row = ELM_PLIST(mat, i+1);
    
    if ( ! IS_PLIST(row) )
      ErrorMayQuit( "Error: Must give a matrix", 0, 0 );
  
    for (j = 0; j < dimension; j = j+1){
      Obj entry_ij = ELM_PLIST(row, j+1);
        if ( IS_INTOBJ(entry_ij) )
          (*A)(j, i) = INT_INTOBJ(entry_ij);
        else if ( IS_MACFLOAT(entry_ij) )
          (*A)(j, i) = VAL_MACFLOAT(entry_ij);
        else
          ErrorMayQuit( "Error: Matrix may only contain integers or floats.", 0, 0 ); 
    }
  }

  //cout << &A << endl <<endl;

  //MatrixXd& B = A;

  //B(0,0)= 2;

  //cout << B << endl <<endl;

  //cout << "Here is the matrix you entered:" << endl << A << endl << endl;

  return NewEigenMatrix(A);

}


Obj ViewEigenMatrix(Obj self, Obj mat)
{
  MatrixXd *A = GET_EIGENMATRIX(mat);
  cout << "Here is the matrix you entered:" << endl << *A << endl << endl;
  return True;
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

Obj Eigensolver(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);

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



Obj EigenEigenvalues(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);

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



Obj EigenEigenvectors(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);

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





Obj EigenSignatureOfSymmetricMatrix(Obj self, Obj mat)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);

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
  double val;
  int pos = 0;
  int neg = 0;
  int null = 0;
  for (i = 0; i < dimension; i = i+1){
    val = es.eigenvalues().col(0)[i].real();
    if (val > 0.0001)
      pos = pos + 1;
    else if (val < -0.0001)
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







Obj EigenSolutionMat(Obj self, Obj mat, Obj vec)
{

  if ( ! IS_PLIST(mat))
          ErrorMayQuit( "Error: Must give a matrix", 0, 0 );

  int dimension = LEN_PLIST(mat);
  if ( LEN_PLIST(ELM_PLIST(mat,1)) != dimension )
      ErrorMayQuit( "Error: Must give an nxn matrix", 0, 0 );

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

  VectorXd V(dimension);

    for (i = 0; i < dimension; i = i+1){
      Obj entry_i = ELM_PLIST(vec, i+1);
        if ( IS_INTOBJ(entry_i) )
          V(i) = INT_INTOBJ(entry_i);
        else if ( IS_MACFLOAT(entry_i) )
          A(i) = VAL_MACFLOAT(entry_i);
        else
          ErrorMayQuit( "Error: Vector may only contain integers or floats.", 0, 0 ); 
    }

//  cout << "Here is the matrix A:\n" << A << endl;
//   cout << "Here is the vector V:\n" << V << endl;

  VectorXd x = A.colPivHouseholderQr().solve(V);
//  cout << "The solution is:\n" << x << endl;
//  cout << "Here is the matrix you entered:" << endl << A << endl << endl;

//  cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
//  cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

   Obj solution = NEW_PLIST(T_PLIST, dimension);
   SET_LEN_PLIST(solution, dimension);
   for (i = 0; i < dimension; i = i+1){
  //   Obj complex_value = NEW_PLIST(T_PLIST, 2);
  //   SET_LEN_PLIST(complex_value, 2);
  //   SET_ELM_PLIST(complex_value, 1, NEW_MACFLOAT(es.eigenvalues().col(0)[i].real()));
  //   SET_ELM_PLIST(complex_value, 2, NEW_MACFLOAT(es.eigenvalues().col(0)[i].imag()));
     SET_ELM_PLIST(solution, i+1, NEW_MACFLOAT(x.col(0)[i]));
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
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", ViewEigenMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", Eigensolver, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenEigenvalues, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenEigenvectors, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenSignatureOfSymmetricMatrix, 1, "mat"),
    GVAR_FUNC_TABLE_ENTRY("EigenGap.c", EigenSolutionMat, 2, "mat, vec"),

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
