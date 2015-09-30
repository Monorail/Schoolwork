-- Alex Berliner
-- al298842
module Test where
import Data.Char

let2nat	::	Char -> Int
let2nat ch = ord ch - ord 'a'

nat2let	::	Int-> Char
nat2let foo = chr(foo + ord 'a')

shift	::	Int-> Char -> Char
shift num ch = nat2let(((let2nat ch) + num) `mod` 26)

encode :: Int -> String -> String
encode num str = map (shift num) str

decode	::	Int-> String -> String
decode num str = map (shift ((-1) * (num))) str

table	::	[Float]
table	=	[8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.2,0.8,4.0,2.4,6.7,7.5,1.9,0.1,6.0,6.3,9.1,2.8,1.0,2.4,0.2,2.0,0.1]


lowers	::	String -> Int
lowers list
	| length list < 1  = 0
	| ord x < ord 'a' || ord x > ord 'z' = lowers (tail list)
	| otherwise = 1 + (lowers (tail list))
	where x = head list
	
count	::	Char -> String -> Int
count ch str 
	| length str < 1 = 0
	| head str == ch = 1 + count ch (tail str)
	| otherwise = count ch (tail str)
	
percent	::	Int -> Int -> Float	
percent a b = ((fromIntegral a)/(fromIntegral b)) * 100

freqs	::	String -> [Float]
freqs str = freqs' ['a'..'z'] str

freqs' :: String -> String -> [Float]
freqs' list str
	| null list = []
	| otherwise = percent (count (head list) str) (lowers str) : freqs' (tail list) str
	
rotate	::	Int -> [a] -> [a]
rotate cy list = (drop cy list) ++ (take cy list)

chisqr :: [Float ] -> [Float] -> Float 
chisqr os es
	| length es < 1 = 0
	| otherwise = ((((head os) - (head es))^2) / (head es)) + (chisqr (tail os) (tail es))
	
position	::	Eq a => a -> [a] -> Int
position val list = positionHelper val list 0

positionHelper :: Eq a=> a -> [a] -> Int -> Int
positionHelper val list count
	| null list = 0
	| (head list) == val = count
	| otherwise = positionHelper val (tail list) (count + 1)
	
	
		
crack :: String -> String
crack str = 
	decode 
	(
		position 
			(minimum [chisqr (rotate n (freqs str)) table | n <- [0..25]])
			[ chisqr (rotate n (freqs str)) table | n <- [0..25] ]
	)
	str

	

	
	
	
	
	
	
	
	
	
	
	
	
	