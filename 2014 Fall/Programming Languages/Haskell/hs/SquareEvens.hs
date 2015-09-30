squareEvens :: [Integer] -> [Integer]
squareEvens list
	| length list < 1			= []
	| even (head list) 			= [(head list) ^ 2] ++ squareEvens (tail list)
	| otherwise 				= [head list] ++ squareEvens (tail list)