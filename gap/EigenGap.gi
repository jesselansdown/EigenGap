#
# EigenGap: Use the Eigen C++ library within GAP
#
# Implementations
#



InstallMethod(ApproximateEigenvaluesOfRealSymmetricMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvaluesOfRealSymmetricMatrix(Float(A));
	end
);

InstallMethod(ApproximateEigenvaluesOfRealMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		return __ApproximateEigenvaluesOfRealMatrix(Float(A));
	end
);

InstallMethod(ApproximateEigenvectorsOfRealSymmetricMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvectorsOfRealSymmetricMatrix(Float(A));
	end
);


InstallMethod(ApproximateEigenvectorsOfRealMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		return __ApproximateEigenvectorsOfRealMatrix(Float(TransposedMat(A)));
	end
);


InstallMethod(ApproximateRankOfRealMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		return __ApproximateRankOfRealMatrix(Float(A));
	end
);


InstallMethod(ApproximateKernelAndImageOfRealMatrix, "",
	[ IsMatrixObj ] ,
	function(A)
		return __ApproximateKernelAndImageOfRealMatrix(Float(TransposedMat(A)));
	end
);


InstallMethod(ApproximateSolutionMat, "",
	[ IsMatrixObj, IsMatrixObj ] ,
	function(A,B)
		return __ApproximateSolutionMat(Float(TransposedMat(A)), Float(TransposedMat(B)));
	end
);


InstallOtherMethod(ApproximateSolutionMat, "",
	[ IsMatrixObj, IsList ] ,
	function(A, B)
		return TransposedMat(__ApproximateSolutionMat(Float(TransposedMat(A)), Float(TransposedMat([B]))))[1];
	end
);

InstallMethod(WithinEpsilon, "",
	[ IsFloat, IsFloat, IsFloat ] ,
	function( x, y, epsilon )
		if AbsoluteValue( x - y ) < AbsoluteValue( epsilon ) then
			return true;
		else
			return false;
		fi;
	end
);
