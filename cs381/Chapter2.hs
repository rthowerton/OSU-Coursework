module Chapter2 where


import Chapter1 hiding (home,pebbles)
import Data.List ( (\\) )


----------------------------------------------------------------------
-- REPRESENTATIONS
----------------------------------------------------------------------

type Size  = Int
type Steps = Int


----------------------------------------------------------------------
-- OPERATIONS ON POSITIONS
----------------------------------------------------------------------


-- Finding the smallest element in a list
--
smallestS :: Size -> Steps
smallestS 1 = 1
smallestS n = 1 + smallestS (n-1)
-- smallestS n = n


-- Finding the closest pebble in a list
--
closestToS :: Size -> Steps
closestToS n = let s = smallestS n + n
                in 1 + n + s
-- closestToS n = 3*n + 1


-- findHome4T :: Pos -> [Pos] -> [Pos]
-- findHome4T c ps | c==home   = [home]
--                 | otherwise = let qs=ps \\ [c]
--                                in c:findHome4T (closestTo c qs) qs

findHomeS :: Size -> Steps
findHomeS 1 = 1
-- findHomeS n = 1 + n + closestToS (n-1) + findHomeS (n-1)
findHomeS n = 2*n^2 + n - 2
