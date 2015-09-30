module DeleteFirst where

deleteFirst :: (Eq a) => a -> [a] -> [a]
deleteFirst a as
	| length as < 1		= []
	| head as /= a 		= (head as) : deleteFirst a (tail as)
	| otherwise 		= tail as