module Chapter5 where


import Data.List (nub)
import Data.Char (toLower)
-- import Data.Tree.Pretty


----------------------------------------------------------------------
-- HISTOGRAMS AS LISTS
----------------------------------------------------------------------

type Histogram = [(Char,Int)]

update :: Histogram -> Char -> Histogram
update []        c = [(c,1)]
update ((k,n):h) c | k==c      = (k,n+1):h
                   | otherwise = (k,n):update h c

extendBy :: Histogram -> String -> Histogram
-- extendBy h []     = h
-- extendBy h (c:cs) = update h c `extendBy` cs
-- extendBy h s = foldl update h s
extendBy = foldl update

hRec = extendBy [] "aba"
--   = update [] 'a' `extendBy` "ba"
--   = update (update [] 'a') 'b' `extendBy` "a"
--   = update (update (update [] 'a') 'b') 'a' `extendBy` ""
--   = update (update (update [] 'a') 'b') 'a'
--
--   = extendBy (update [] 'a') "ba"
--   = extendBy (update (update [] 'a') 'b') "a"
--   = extendBy (update (update (update [] 'a') 'b') 'a') ""
--   = update (update (update [] 'a') 'b') 'a'
hExp = update (update (update [] 'a') 'b') 'a'

h1 = [] `extendBy` "God"
h2 = h1 `extendBy` "Iehova"
h3 = h2 `extendBy` "Jehova"
-- h4 = h3 `extendBy` "Yahweh"
h4 = h3 `extendBy` (nub "Yahweh")
h5 = h4 `extendBy` "Yehova"

addWords :: Histogram -> [String] -> Histogram
addWords h []     = h
addWords h (w:ws) = h `extendBy` (nub w) `addWords` ws
-- addWords h ws = foldl extendBy h (map nub ws)

h = addWords [] ["God","Iehova","Jehova","Yahweh","Yehova"]


----------------------------------------------------------------------
-- HISTOGRAMS AS BINARY SEARCH TREES
----------------------------------------------------------------------

data Tree a = Node a (Tree a) (Tree a)
            | Empty
            deriving Show

type HistogramT = Tree (Char,Int)

--- updateT :: HistogramT -> Char -> HistogramT
-- updateT Empty            c             = Node (c,1) Empty Empty
-- updateT (Node (k,n) l r) c | c==k      = Node (k,n+1) l r
--                            | c<k       = Node (k,n) (updateT l c) r
--                            | otherwise = Node (k,n) l (updateT r c)

updateT :: HistogramT -> Char -> HistogramT
updateT Empty            c                        = Node (c,1) Empty Empty
updateT (Node (k,n) l r) c | toLower c==toLower k = Node (k,n+1) l r
                           | toLower c<toLower k  = Node (k,n) (updateT l c) r
                           | otherwise            = Node (k,n) l (updateT r c)

extendByT :: HistogramT -> String -> HistogramT
extendByT = foldl updateT

t1 = Empty `extendByT` "God"
t2 = t1 `extendByT` "Iehova"
t3 = t2 `extendByT` "Iehova"
t4 = t3 `extendByT` (nub "Yahweh")
t5 = t4 `extendByT` "Yehova"

addWordsT :: HistogramT -> [String] -> HistogramT
addWordsT h ws = foldl extendByT h (map nub ws)

t = addWordsT Empty ["God","Iehova","Jehova","Yahweh","Yehova"]

pT :: Show a => Tree a -> IO ()
pT t = putStr (showT t)
-- pT = putStr . showT

showT :: Show a => Tree a -> String
showT = showTS ""

showTS :: Show a => String -> Tree a -> String
showTS s Empty = s++"-\n"
showTS s (Node x Empty Empty) = s++show x++"\n"
showTS s (Node x l r) = let v=s++show x++"\n"
                            s'=replicate (length v) ' '
                         in showTS s' r++v++showTS s' l
-- showTS s (Node x l r) = let s'=s++replicate (length (show x)+1) ' '
--                          in showTS s' r++s++show x++"\n"++showTS s' l


----------------------------------------------------------------------
-- STILL TREES
----------------------------------------------------------------------

ws = ["bat","bag","beg","bet","mag","mat","meg","met"]
ws' = ["bag","bat","beg","bet","mag","mat","meg","met"]

insert :: String -> Tree String -> Tree String
insert s Empty                    = Node s Empty Empty
insert s (Node x l r) | s==x      = Node x l r
                      | s<x       = Node x (insert s l) r
                      | otherwise = Node x l (insert s r)

build :: [String] -> Tree String
-- build ws = foldl (flip insert) Empty ws
build = foldl (flip insert) Empty

bst = build ws


----------------------------------------------------------------------
-- TRIES
----------------------------------------------------------------------

type Trie = Tree Char

tr1 = insertT "mat" (insertT "map" Empty)
tr2 = insertT "max" tr1
tr3 = buildT ["bag","bat","beg","bet"]

tws  = buildT ws
tws' = buildT ws'

-- tr3 = insertT "mate" (insertT "maps" tr2)


pTr :: Trie -> IO ()
pTr = putStrLn . showTr

showTr :: Trie -> String
showTr = showTrS "" False

indent :: String -> Bool -> Char -> String
-- indent s b c = (if b then s else "")++"c"
indent s True  c = s++[c]
indent s False c = [c]

showTrS :: String -> Bool -> Trie -> String
showTrS _ _ Empty = ""
showTrS s b (Node c Empty Empty) = indent s b c
showTrS s b (Node c l Empty)     = indent s b c ++ showTrS ('.':s) False l
showTrS s b (Node c l r)         = indent s b c ++ showTrS ('.':s) False l++"\n"
                                                ++ showTrS s True r


insertT :: String -> Trie -> Trie
insertT []     t                        = t
insertT (c:cs) Empty                    = Node c (insertT cs Empty) Empty
insertT (c:cs) (Node x l r) | x==c      = Node x (insertT cs l) r
                            | otherwise = Node x l (insertT (c:cs) r)
-- switch left/right
-- insertT (c:cs) Empty = Node c Empty (insertT cs Empty)
-- insertT (c:cs) (Node x l r) | x==c      = Node x l (insertT cs r)
--                             | otherwise = Node x (insertT (c:cs) l) r


buildT :: [String] -> Trie
-- build ws = foldl (flip insert) Empty ws
buildT = foldl (flip insertT) Empty
