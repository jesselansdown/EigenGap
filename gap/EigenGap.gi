#
# EigenGap: Use the Eigen C++ library within GAP
#
# Implementations
#



InstallMethod(ApproximateEigenvaluesOfRealSymmetricMatrix, "",
	[ IsList ] ,
	function(A)
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvaluesOfRealSymmetricMatrix(Float(A));
	end
);

InstallMethod(ApproximateEigenvaluesOfRealMatrix, "",
	[ IsList ] ,
	function(A)
		return __ApproximateEigenvaluesOfRealMatrix(Float(A));
	end
);

InstallMethod(ApproximateEigenvectorsOfRealSymmetricMatrix, "",
	[ IsList ] ,
	function(A)
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvectorsOfRealSymmetricMatrix(Float(A));
	end
);


InstallMethod(ApproximateEigenvectorsOfRealMatrix, "",
	[ IsList ] ,
	function(A)
		if TransposedMat(A)<>A then
			Print("Warning! This method only works for symmetric real matrices!\n");
		fi;
		return __ApproximateEigenvectorsOfRealMatrix(Float(A));
	end
);


InstallMethod(ApproximateRankOfRealMatrix, "",
	[ IsList ] ,
	function(A)
		return __ApproximateRankOfRealMatrix(Float(A));
	end
);
