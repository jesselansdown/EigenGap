The GAP 4 package `EigenGap'
==============================

This package uses the C++ Library "Eigen" to provide extra eigenvalue functionality in GAP.

To install, place in the "pkg" directory of GAP and run the following commands:

- ./autogen.sh
- ./configure
- make

Currently only the following functions are implemented:

EigenEigenvalue( mat );

- Takes a nxn matrix of integers or floats (or a list of lists, since floating values are not considered matrices in the GAP sense)
- Returns a list of the eigenvalues, where each eigenvalue is a list containing the real component in the first entry, and the imaginary component in the second entry.

EigenEigenvectors( mat );

- Takes a nxn matrix of integers or floats (or a list of lists, since floating values are not considered matrices in the GAP sense)
- Returns a list of the eigenvectors, where each eigenvector entry is a list containing the real component in the first entry, and the imaginary component in the second entry.

Eigensolver( mat );

- Returns both the eigenvalues and eigenvectors. This function is currently buggy for large matricies.

EigenSignatureOfSymmetricMatrix( mat);

- Returns the signature of a symmetric matrix: [# positive eigenvalues, # zero eigenvalues, # negative eigenvalues]

EigenSolutionMat

- Functions in the same way as SolutionMat in GAP (only currently takes an nxn matrix).