module Sub1List where
sub1_list_rec :: [Integer] -> [Integer]
sub1_list_comp :: [Integer] -> [Integer]


sub1_list_comp x = [a - 1 | a <- x]


sub1_list_rec x 
	| length x < 1		= []
	| otherwise 		= [(head x)-1] ++ sub1_list_rec (tail x)
