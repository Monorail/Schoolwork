module Simplify where
import StatementsExpressions

simplify :: Statement -> Statement
simplify (IfStmt (VarExp "true") stmt) = (simplify stmt)
simplify (ExpStmt exp) = ExpStmt (exprConvert exp)
simplify (AssignStmt str exp) = AssignStmt str (exprConvert exp)
simplify (IfStmt exp stmt) = IfStmt (exprConvert exp) (simplify stmt)
simplify s = s

exprConvert :: Expression -> Expression
exprConvert (BeginExp [] exp) = (exprConvert exp)
exprConvert (BeginExp stmt exp) = BeginExp (map simplify stmt) (exprConvert exp)
exprConvert (EqualsExp exp1 exp2) = EqualsExp (exprConvert exp1) (exprConvert exp2)
exprConvert exp = exp