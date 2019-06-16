module Chapter3 where


----------------------------------------------------------------------
-- REPRESENTATIONS
----------------------------------------------------------------------

type Digit   = Int
type Decimal = [Digit]

----------------------------------------------------------------------
-- OPERATIONS
----------------------------------------------------------------------

isDigit :: Digit -> Bool
isDigit d = 0<=d && d<=9


-- Representing integers by Decimal values
--
decFromInt :: Int -> Decimal
decFromInt i | isDigit i = [i]
             | i>9       = decFromInt (i `div` 10) ++ [i `mod` 10]

decToInt :: Decimal -> Int
decToInt [d]    = d
decToInt (d:ds) = 10^(length ds)*d + decToInt ds
-- decToInt (d:ds) = let n=length ds
--                 in 10^n*d + decToInt ds

-- revToInt :: [Int] -> Int
-- revToInt [d]    = d
-- revToInt (d:ds) = d + 10*revToInt ds

-- decToInt :: Decimal -> Int
-- decToInt d = revToInt (reverse d)

addZero :: Decimal -> Decimal
addZero is = is ++ [0]
