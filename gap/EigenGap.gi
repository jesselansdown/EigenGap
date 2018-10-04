#
# EigenGap: Use the Eigen C++ library within GAP
#
# Implementations
#



InstallMethod(SignatureOfComplexHermitianMatrix, "",
	[ IsList] ,
	function(mat)
		local i, j;
		if not IsList(mat[1]) then
			Print("Error: must give a matrix\n");
			return fail;
		fi;
		if Size(mat) <> Size(mat[1]) then
			Print("Error: must give a square matrix\n");
			return fail;
		fi;
		for i in [1 .. Size(mat)] do
			for j in [i .. Size(mat)] do
				if mat[i][j][1] <> mat[j][i][1] then
					Print("Error: must give a hermitian matrix\n");
					return fail;
				fi;
				if mat[i][j][2] <> -mat[j][i][2] then
					Print("Error: must give a hermitian matrix\n");
					return fail;
				fi;
			od;
		od;
		return SignatureOfComplexHermitianMatrixNC( mat );
	end
);

InstallMethod(SignatureOfComplexHermitianMatrix, "",
	[ IsList, IsFloat ] ,
	function(mat, tol)
		local i, j;
		if not IsFloat(tol) then
			Print("Error: tolerance must be a float\n");
			return fail;
		fi;
		if not IsList(mat[1]) then
			Print("Error: must give a matrix\n");
			return fail;
		fi;
		if Size(mat) <> Size(mat[1]) then
			Print("Error: must give a square matrix\n");
			return fail;
		fi;
		for i in [1 .. Size(mat)] do
			for j in [i .. Size(mat)] do
				if mat[i][j][1] <> mat[j][i][1] then
					Print("Error: must give a hermitian matrix\n");
					return fail;
				fi;
				if mat[i][j][2] <> -mat[j][i][2] then
					Print("Error: must give a hermitian matrix\n");
					return fail;
				fi;
			od;
		od;
		return SignatureOfComplexHermitianMatrixNC( mat , tol );
	end
);

InstallMethod(SignatureOfComplexHermitianMatrixNC, "",
	[ IsList ] ,
	function(mat)
		local mat2;
		mat2 := EigenComplexMatrix(mat);
		return __SignatureOfComplexHermitianMatrix( mat2 , Size(mat) );
	end
);


InstallMethod(SignatureOfComplexHermitianMatrixNC, "",
	[ IsList, IsFloat] ,
	function(mat, tol)
		local mat2;
		mat2 := EigenComplexMatrix(mat);
		return __SignatureOfComplexHermitianMatrix( mat2 , Size(mat), tol );
	end
);
