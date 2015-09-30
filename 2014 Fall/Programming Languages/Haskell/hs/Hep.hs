module Hep where
hep :: [Word] -> [Word]
type Word = String
hep list
	| null list	= []
	| take 3 list == ["by","the","way"] 		= "btw" : hep (drop 3 list)
	| take 3 list == ["for","your","information"]= "fyi" : hep (drop 3 list)
	| take 3 list == ["be","right","back"]		= "brb" : hep (drop 3 list)
	| take 3 list == ["laughing","out","loud"]	= "lol" : hep (drop 3 list)
	| take 2 list == ["see", "you"]				= "cya" : hep (drop 2 list)
	| take 1 list == ["you"] 			= "u"	: hep (tail list)
	| take 1 list == ["are"] 			= "r"	: hep (tail list)
	| take 1 list == ["your"] 			= "ur"	: hep (tail list)
	| take 1 list == ["you"] 			= "u"	: hep (tail list)
	| take 1 list == ["boyfriend"] 		= "bf"	: hep (tail list)
	| take 1 list == ["girlfriend"] 	= "gf"	: hep (tail list)
	| take 1 list == ["great"] 			= "gr8"	: hep (tail list)
	| otherwise 					= (take 1 list) ++ hep (tail list)
