module BinaryRelationOps where
import BinaryRelation

project1 :: (BinaryRelation a b) -> [a]
project1 list = [fst x|x<-list]

project2 :: (BinaryRelation a b) -> [b]
project2 list = [snd x|x<-list]

select :: ((a,b) -> Bool) -> (BinaryRelation a b) -> (BinaryRelation a b)
select pred list = [x | x <- list, pred x]

compose :: Eq b => (BinaryRelation a b) -> (BinaryRelation b c) -> (BinaryRelation a c)
compose list1 list2 = [(fst x,snd y) | x <- list1, y <- list2, snd x == fst y]