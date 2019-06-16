module Chapter4S where


import Chapter4 hiding (baskervilles)
import Data.Array


-- Exercise 20
--
removeAt :: Int -> [People] -> [People]
removeAt 1 (x:xs) = xs
removeAt n (x:xs) = x:removeAt (n-1) xs


-- Exercise 21
--
clear :: People -> Array People Bool -> Array People Bool
clear p a = a // [(p,False)]


-- Exercise 22
--
single :: String -> String -> Tree
single p c = Node p [leaf c]

baskervilles :: Tree
baskervilles = Node "Hugo" [leaf "Charles",
                            single "John" "Henry",
                            single "Rodger" "Stapleton",
                            leaf "Elizabeth"]


-- Exercise 23
--
insert2 :: People -> [People] -> [People]
insert2 p ps | member p ps = ps
             | otherwise   = p:ps

remove2 :: People -> [People] -> [People]
remove2 q []                 = []
remove2 q (p:ps) | p==q      = ps
                 | otherwise = p:remove q ps


-- Exercise 24
--
asArray :: [People] -> Array People Bool
asArray ps = empty // [(p,True) | p <- ps]


-- Exercise 25
--
mergeQ :: [People] -> [People] -> [People]
mergeQ [] ps = ps
mergeQ ps [] = ps
mergeQ (p:ps) (q:qs) = p:q:mergeQ ps qs
