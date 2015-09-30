-- $Id: Polynomials.hs,v 1.3 2013/08/18 16:42:00 leavens Exp leavens $
module Polynomials where

-- Polynomials are represented by finite lists of coefficients,
-- with the zeroth coefficient being the constant (representing x^0)
-- and the nth (zero-based) coefficient multiplied by x^n.
-- For example, the polynomial 0.0 is represented by both [] and [0.0].
-- Also 4.1x + 5.0 is represented by [5.0, 4.1] both and [5.0, 4.1, 0.0].
-- 4.1x^2 + 2.2x + 5.7 is represented by [5.7, 2.2, 4.1].
type Polynomial = [Double]
evaluate :: Polynomial -> Double -> Double
scaleBy :: Double -> Polynomial -> Polynomial
add :: Polynomial -> Polynomial -> Polynomial
sub :: Polynomial -> Polynomial -> Polynomial

-- evaluate p x is the value of the polynomial p where the unknown is x.
-- So evaluate [5.7, 2.2, 4.1] 10.0 is 5.7 + 2.2*10.0 + 4.1*10.0^2
evaluate p x = eval p x 0.0 0
    where eval :: Polynomial -> Double -> Double -> Int -> Double
          eval [] x acc expon = acc
          eval (c:cs) x acc expon = eval cs x (acc + c*(x^expon)) (expon+1)

		  
-- scaleBy returns the Polynomial with each coefficient multiplied by the Double
scaleBy coef poly
	| length poly < 1	= []
	| otherwise 		= [(head poly) * coef] ++ scaleBy coef (tail poly)

-- add returns a Polynomial that is the sum of the two arguments.
add poly1 poly2
	| length poly1 < length poly2	= add (poly1++[0]) poly2
	| length poly1 > length poly2	= add (poly2++[0]) poly1
	| length poly1 < 1	= []
	| otherwise 		= [(head poly1) + (head poly2)] ++ add (tail poly1) (tail poly2)
	
-- sub returns the second argument Polynomial subtracted from the first
-- WRITE YOUR CODE HERE
--[] [1,2,3,4]
sub poly1 poly2 -- [] [40.20] => [0] [40.20]
	| length poly1 < length poly2	= sub (poly1++[0]) poly2
	| length poly1 > length poly2	= sub poly1 (poly2++[0])
	| length poly1 < 1	= []
	| otherwise 		= [(head poly1) - (head poly2)] ++ sub (tail poly1) (tail poly2)
	
	
-- [1,2,3] [1,2,3,4,5]
-- [2] + [4] + [6] + [4,5]
add p1 [] = p1 -- if add is passed a list followed by an empty list return p1
add [] p2 = p2 -- if add is passed an empty list followed by a list return p2
add p1 p2 = head p1 + head p2 : add (tail p1) (tail p2)
	
	
--p1 [1,2,3,4,5]
--p2     [1,2,3]