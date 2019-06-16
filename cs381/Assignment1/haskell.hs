module Pt2 where
	--Define abstrct syntax as a Haskell data type
	data Circuit = C Gates Links
		deriving Show

	data Gate   = G Int GateFn
		deriving Show

	data GateFn = And | Or | Xor | Not
		deriving Show

	data Link   = From Int Int Int Int
		deriving Show

	type Gates = [Gate]

	type Links = [Link]

	--Represent half adder circuit in abstract syntax
	halfadder = C [(G 1 Xor), (G 2 And)] [(From 1 1 2 1), (From 1 2 2 2)]

	--Define a Haskell function that implements a pretty printer for the abstract syntax
	printHalfAdder :: Circuit -> String
	printHalfAdder = ""
	printHalfAdder (C gates links) = printHalfAdder(gates) printHalfAdder(links)
	printHalfAdder ((G i g):gs) = putStrLn (i ++ ":" ++ g ++ ";\n") printHalfAdder(gs)
	printHalfAdder ((From a b c d):ls) = putStrLn("from " ++ a ++ "." ++ b ++ " to " ++ c ++ "." ++ d ++ ";\n")

	{-printGates :: Gates -> String
	printGates = ""

	printLinks :: Links -> String
	printLinks = ""-}