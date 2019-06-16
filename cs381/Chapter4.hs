{-# LANGUAGE FlexibleInstances #-}

module Chapter4 where


-- import Chapter1 hiding (home,pebbles)
-- import Data.List ( (\\) )
import Data.Array

----------------------------------------------------------------------
-- LISTS
----------------------------------------------------------------------

suspects :: [String]
suspects = ["Mortimer","Beryl","Selden"]

-- data List = Empty | Cons Int List
-- data List = Empty | Cons String List
data List a = Empty | Cons a (List a)
            --   deriving Show

suspectsList :: List String
suspectsList = Cons "Mortimer" (Cons "Beryl" (Cons "Selden" Empty))


data People = Mortimer | Desmond | Jack | Beryl | Selden
              deriving (Eq,Ord,Show,Ix)

suspectsL :: [People]
suspectsL = [Mortimer,Beryl,Selden]

find :: People -> [People] -> Bool
find _ []                 = False
find y (x:xs) | x==y      = True
              | otherwise = find y xs

lookUp :: Int -> [People] -> People
lookUp 1 (x:xs) = x
lookUp n (x:xs) = lookUp (n-1) xs

insertAt :: People -> Int -> [People] -> [People]
insertAt y 1 xs     = y:xs
insertAt y n (x:xs) = x:insertAt y (n-1) xs


----------------------------------------------------------------------
-- ARRAYS
----------------------------------------------------------------------

suspectsA :: Array People Bool
suspectsA = array (Mortimer,Selden)
  [(Mortimer,True),(Desmond,False),(Jack,False),(Beryl,True),(Selden,True)]

asList :: Array People Bool -> [People]
asList a = [p | (p,b) <- assocs a, b]


----------------------------------------------------------------------
-- TREES
----------------------------------------------------------------------


data Tree = Node String [Tree]
            deriving Show

leaf :: String -> Tree
leaf s = Node s []

baskervilles :: Tree
baskervilles = Node "Hugo" [leaf "Charles",
                            Node "John" [leaf "Henry"],
                            Node "Rodger" [leaf "Stapleton"],
                            leaf "Elizabeth"]

inheritance :: Tree -> [String]
inheritance (Node p cs) = p:concat [inheritance c | c <- cs]
-- inheritance (Node p cs) = p:concatMap inheritance cs


----------------------------------------------------------------------
-- DATS TYPES ~ TYPE CLASSES
----------------------------------------------------------------------

class PeopleSet s where
  empty   :: s
  isEmpty :: s -> Bool
  member  :: People -> s -> Bool
  insert  :: People -> s -> s
  remove  :: People -> s -> s

class Dict d where
  emptyD  :: d k a
  lookupD :: k -> d k a -> Maybe a
  insertD :: k -> a -> d k a -> d k a
  removeD :: k -> d k a -> d k a

class PeopleStack s where
  emptyS   :: s
  isEmptyS :: s -> Bool
  push     :: People -> s -> s
  top      :: s -> People
  pop      :: s -> s

class PeopleQueue q where
  emptyQ   :: q
  isEmptyQ :: q -> Bool
  enqueue  :: People -> q -> q
  front    :: q -> People
  dequeue  :: q -> q

----------------------------------------------------------------------
-- IMPLEMENTATIONS OF DATA TYPES ~ TYPE CLASSE INSTANCES
----------------------------------------------------------------------

instance PeopleSet [People] where
  empty = []
  isEmpty ps = ps==[]
  member p ps = find p ps
  insert p ps = p:ps
  remove q []                 = []
  remove q (p:ps) | p==q      = remove q ps
                  | otherwise = p:remove q ps

instance PeopleSet (Array People Bool) where
  empty = array (Mortimer,Selden) [(p,False) | p <- range (Mortimer,Selden)]
  isEmpty a = a==empty
  member p a = a ! p
  insert p a = a // [(p,True)]
  remove p a = a // [(p,False)]

-- type ListDict k a = [(k,a)]
-- newtype ListDict k a = L [(k,a)]
--
-- instance Dict ListDict where
--   emptyD = L []
--   lookupD k (L xs) = lookup k xs
--   insertD k x (L xs) = L ((k,x):xs)
--   removeD k (L xs) = L [(l,x) | (l,x) <- xs, l/=k]

instance PeopleStack [People] where
  emptyS = []
  isEmptyS ps = ps==[]
  -- push p ps  = p:ps
  -- top (p:ps) = p
  -- pop (p:ps) = ps
  push = (:)
  top = head
  pop = tail

instance PeopleQueue [People] where
  emptyQ = []
  isEmptyQ ps = ps==[]
  enqueue p ps = ps ++ [p]
  front = head
  dequeue = tail
