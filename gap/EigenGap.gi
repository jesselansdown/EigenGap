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
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvectorsOfRealMatrix(Float(A));
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
		return __ApproximateKernelAndImageOfRealMatrix(Float(A));
	end
);
