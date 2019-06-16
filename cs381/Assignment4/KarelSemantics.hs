module KarelSemantics where

import Prelude hiding (Either(..))
import Data.Function (fix)

import KarelSyntax
import KarelState

--Author: Cooper Hutchins (and no-one else!)


-- | Valuation function for Test.
test :: Test -> World -> Robot -> Bool
test (Not t) w r    = (case (test t w r) of
                       False -> True
		       True  -> False)
test (Facing d) w r = (if (getFacing r) == d then True else False)
test (Clear d) w r  = (if (isClear (relativePos d r) w) then True else False)
test (Beeper) w r   = (if (hasBeeper (getPos r) w) then True else False)
test (Empty) w r    = (if (isEmpty r) then True else False)

-- | Valuation function for Stmt.
stmt :: Stmt -> Defs -> World -> Robot -> Result
stmt Shutdown   _ _ r = Done r
stmt PickBeeper _ w r = let p = getPos r
                        in if hasBeeper p w
                              then OK (decBeeper p w) (incBag r)
                              else Error ("No beeper to pick at: " ++ show p)
stmt PutBeeper _ w r  = if(isEmpty r) == False then 
                                      OK (incBeeper (getPos r) w) (decBag r)
				      else Error ("No beepers to place")
stmt (Turn d) _ w r   = OK w (updateFacing (cardTurn d) r)
stmt Move _ w r       = if(isClear (neighbor (getFacing r) (getPos r)) w) then
                           OK w (setPos (neighbor (getFacing r) (getPos r)) r)
			   else Error ("Blocked at " ++ show (neighbor (getFacing r) (getPos r)))

stmt (Block s) d w r  = block s d w r

stmt (Call m) d w r   = macro m d w r

stmt (If t s a) d w r = case (test t w r) of
                        True  -> stmt s d w r
			False -> stmt a d w r

stmt (While t s) d w r = case (test t w r) of
                         True  -> case (stmt s d w r) of
			          OK l v  ->  stmt (While t s) d (case (stmt s d w r) of OK y p -> y) (case (stmt s d w r) of OK y p -> p)
			          Error s -> Error s
			          Done w  -> Done w
			 False -> OK w r

stmt (Iterate 0 s) d w r = OK w r
stmt (Iterate n s) d w r = case (stmt s d w r) of
                           OK i j  -> stmt (Iterate (n-1) s) d (case (stmt s d w r) of OK y p -> y) (case (stmt s d w r) of OK y p -> p)
			   Error s -> Error s
			   Done z  -> Done z

macro :: String -> Defs -> World -> Robot -> Result          
macro s [] w r     = Error ("Macro '" ++ s ++ "' not found");
macro s ((n,st):dn) w r = if (n == s) 
                          then (stmt st dn w r) 
		          else (macro s dn w r)

block :: [Stmt] -> Defs -> World -> Robot -> Result          
block [] d w r = OK w r
block (h:t) d w r = case (stmt h d w r) of 
                    OK y p  -> block t d (case (stmt h d w r) of OK w r -> w) (case (stmt h d w r) of OK w r -> r)
		    Done q  -> Done q
		    Error s -> Error s

-- | Run a Karel program.
prog :: Prog -> World -> Robot -> Result
prog (m,s) w r = stmt s m w r
