module ListMax where


listMax :: (Ord a) => [a] -> a
listMax [x] = x
listMax (x:xs)
    | x > (listMax xs) 	= x
    | otherwise 		= (listMax xs)