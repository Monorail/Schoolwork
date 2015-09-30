module WhatIndex where

whatIndex :: (Eq a) => a -> [a] -> Integer
whatIndex sought lst = index lst 0 where
		index [] _ = -1
		index (x:xs) i
			| sought /= x = index xs (i+1)
			| sought == x = i


	-- | x == sought 				= 0
	-- | whatIndex sought xs == -1	= -1
	-- | otherwise					= 1 + whatIndex sought xs