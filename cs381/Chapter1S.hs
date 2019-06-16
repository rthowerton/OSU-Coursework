module Chapter1S where

import Chapter1 hiding (pebbles)
import Data.List ( (\\) )


-- Exercise 6
--
moveUpBy :: Float -> Pos -> Pos
moveUpBy n (x,y) = (x,y+n)


-- Exercise 7
--
moveBy :: Float -> Float -> Pos -> Pos
moveBy h v (x,y) = (x+h,y+v)


-- Exercise 8
--
pebbles :: [Pos]
pebbles = (9,8):(6,8.5):home:[]


-- Exercise 9
--
last :: [Pos] -> Pos
last ps = head (reverse ps)


-- Exercise 10
--
myMin :: Float -> Float -> Float
-- myMin x y = if x<=y then x else y
myMin x y | x<=y      = x
          | otherwise = y


-- Exercise 11
--
{-
(a) Yes, the list [home].
More generally, any list that contains home and whose other positions
are farther away from the starting position than home.

(b) Yes, if we use a position that is closer to home than to any
other position. Try: findHome1 (4,4) pebbles
-}

-- Exercise 12
--
{-
No. A simple example is findHome3 home [(9,9),home]. FincdHome will identify home as the next position and terminate and never select (9,9).
-}


-- Exercise 13
--
findPath :: Pos -> Pos -> [Pos] -> Pos
findPath from to ps | from==to  = to
                    | otherwise = findPath (closestTo from ps) to (ps \\ [from])

findHome :: Pos -> [Pos] -> Pos
findHome c ps = findPath c home ps


-- Exercise 14
--
-- No. Try: findHome3T (4,4) [(9,9),(8,8),(3,3),home]
findHome3T :: Pos -> [Pos] -> [Pos]
findHome3T c ps | c==home   = [home]
                | otherwise = let qs=ps
                               in c:findHome3T (closestTo c ps) (ps \\ [c])

{-
> findHome3T (1,1) [(2,2),(3,3),home]
[(1.0,1.0),(2.0,2.0),(2.0,2.0),(3.0,3.0),(3.0,3.0),(3.0,4.5)]

The problem is that intermediate positions are visited twice. The solution
is to remove the current position before calling closestTo.
-}

findHome4T :: Pos -> [Pos] -> [Pos]
findHome4T c ps | c==home   = [home]
                | otherwise = let qs=ps \\ [c]
                               in c:findHome4T (closestTo c qs) qs

{-
> findHome4T (1,1) [(2,2),(3,3),home]
[(1.0,1.0),(2.0,2.0),(3.0,3.0),(3.0,4.5)]
-}
