module Caesar where
import Data.Char

let2nat	::	Char -> Int
let2nat ch = ord ch - ord 'a'

nat2let	::	Int -> Char
nat2let num = chr (num + ord 'a')

shift	::	Int -> Char -> Char
shift num ch
	| ch < 'a' || ch > 'z' 	= ch
	| otherwise = (cycle ['a'..'z']) !! ((let2nat ch) + num + 26)
	
encode :: Int -> String -> String
encode num str = map (shift num) str

decode	::	Int -> String -> String
decode num str = map (shift (negate num)) str