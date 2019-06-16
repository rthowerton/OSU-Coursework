module Exercise3 where

data Cmd = Pen Mode
		 | MoveTo Int Int
		 | Seq Cmd Cmd
		 deriving Show

data Mode = Up | Down deriving Show

type State = (Mode, Int, Int)
type Line = (Int, Int, Int, Int)
type Lines = [Line]

semS :: Cmd -> State -> (State, Lines)
semS (Pen m) (mode, numA, numB) = ((m, numA, numB), [(numA, numB, numA, numB)])
semS (MoveTo x y) (mode, numA, numB) = ((mode, x, y), [(numA, numB, x, y)])
semS (Seq cmdA cmdB) state = (state2, lines)
	where (state1, line1) = semS cmdA state
		  (state2, line2) = semS cmdB state1
		  lines           = line1 ++ line2

sem' :: Cmd -> Lines
sem' c = snd(semS c (Up, 0, 0))