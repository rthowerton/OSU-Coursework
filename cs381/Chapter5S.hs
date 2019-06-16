module Chapter5S where


import Chapter5 -- hiding (addWords)
import Data.List (nub)


-- Exercise 26
--
remDup :: String -> String
remDup []     = []
remDup (c:cs) = c:remDup [c | d <- cs, d /= c]


-- Exercise 27
--
maxCount :: Histogram -> (Int,String)
maxCount h = let m = maximum [n | (c,n) <- h]
              in (m,[c | (c,n) <- h, n == m])


-- Exercise 28
--
addWords :: Histogram -> [String] -> Histogram
addWords h ws = foldl extendBy h (map nub ws)


-- Exercise 29
--
frequency :: Char -> Histogram -> Int
frequency c []                    = 0
frequency c ((k,n):h) | k==c      = n
                      | otherwise = frequency c h


-- Exercise 30
--
inorder :: Tree a -> [a]
inorder Empty = []
inorder (Node x l r) = inorder l ++ [x] ++ inorder r


-- Exercise 31
--
maxCountT :: HistogramT -> (Int,String)
maxCountT h = maxCount (inorder h)
-- maxCountT = maxCount . inorder


-- Exercise 32
--
frequencyT :: Char -> HistogramT -> Int
frequencyT c Empty                        = 0
frequencyT c (Node (k,n) l r) | c==k      = n
                              | c<k       = frequencyT c l
                              | otherwise = frequencyT c r


-- Exercise 33
--
treeSort :: [String] -> [String]
-- treeSort ws = inorder (foldl (flip insert) Empty ws)
-- treeSort ws = inorder (build ws)
treeSort = inorder . build
