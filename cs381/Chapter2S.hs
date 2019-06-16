module Chapter2S where


import Chapter1 (smallest)
import Chapter2
import Data.List ( (\\) )


-- Exercise 15
--
snoc :: Int -> [Int] -> [Int]
snoc x []     = [x]
snoc x (y:ys) = y:snoc x ys

snocS :: Size -> Steps
snocS 0 = 1
snocS n = 1 + snocS (n-1)
-- snocS n = n + 1


-- Exercise 16
--
sndSmallest :: [Float] -> Float
sndSmallest xs = smallest (xs \\ [smallest xs])

sndSmallestS :: Size -> Steps
-- sndSmallestS n = smallestS n + smallestS (n-1)
-- sndSmallestS n = n + n - 1
sndSmallestS n = 2*n - 1
