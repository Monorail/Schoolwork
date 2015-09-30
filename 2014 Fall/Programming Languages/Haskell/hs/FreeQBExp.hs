module FreeQBExp where
import QBExp 
import DeleteFirst
freeQBExp :: QBExp -> [String]
freeQBExp (Varref str) = [str]

freeQBExp (Exists str qb) = deleteFirst str (freeQBExp qb)

freeQBExp (qb1 `Or` qb2)
	| setEqual (freeQBExp qb1) (freeQBExp qb2) = freeQBExp qb1
	| otherwise = (freeQBExp qb1) ++ (freeQBExp qb2)



	
setEqual los1 los2 = (length los1) == (length los2) && subseteq los1 los2
subseteq los1 los2 = all (\e -> e `elem` los2) los1