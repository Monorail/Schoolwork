module EqOptim where
import StatementsExpressions

eqOptim :: Statement -> Statement	
eqOptim (ExpStmt exp) = ExpStmt (exOptim exp)
eqOptim (AssignStmt str exp) = AssignStmt str (exOptim exp)
eqOptim (IfStmt exp stmt) = IfStmt (exOptim exp) (eqOptim stmt)
	
	
exOptim :: Expression -> Expression
exOptim (EqualsExp (VarExp exp1) (VarExp exp2))
	| exp1 == exp2 = (VarExp "true")
	| otherwise = (EqualsExp (VarExp exp1) (VarExp exp2))
exOptim (BeginExp stmt exp) = BeginExp (map eqOptim stmt) (exOptim exp)
exOptim exp = exp