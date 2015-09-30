module Rotate where
import Amount

rotate :: Amount -> (a,a,a) -> (a,a,a)
rotate Zero x = (first x, second x, third x)
rotate One x = (third x, first x, second x)
rotate Two x = (second x, third x, first x)


first :: (a, b, c) -> a
first (x, _, _) = x
  
second :: (a, b, c) -> b
second (_, y, _) = y
  
third :: (a, b, c) -> c
third (_, _, z) = z