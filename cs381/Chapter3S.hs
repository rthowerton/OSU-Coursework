module Chapter3S where


import Chapter3 hiding (isDigit)


-- Exercise 17
--
isDigit :: Digit -> Bool
isDigit d = 0<=d && d<=9

isDecimal :: Decimal -> Bool
isDecimal []     = False
isDecimal [d]    = isDigit d
isDecimal (d:ds) = isDigit d && isDecimal ds


-- Exercise 18
--
type Bit    = Int
type Binary = [Bit]

isBit :: Bit -> Bool
isBit b = b==0 || b==1

isBinary :: Binary -> Bool
isBinary []     = False
isBinary [d]    = isBit d
isBinary (d:ds) = isBit d && isBinary ds

binFromInt :: Int -> Binary
binFromInt b | isBit b = [b]
             | b>1     = binFromInt (b `div` 2) ++ [b `mod` 2]

binToInt :: Binary -> Int
binToInt [b]    = b
-- binToInt (b:bs) = let n=length bs
--                    in 2^n*b + binToInt bs
binToInt (b:bs) = 2^(length bs)*b + binToInt bs


-- Exercise 19
--
div10 :: Decimal -> Decimal
div10 [d]    = [0]
div10 [d,d'] = [d]
div10 (d:ds) = d:div10 ds

-- addDigits :: Digit -> Digit -> (Digit,Digit)
-- addDigits d d' = (div (d+d') 10,mod (d+d') 10)
