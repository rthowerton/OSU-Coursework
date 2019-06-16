
type Minute = Int
type Hour   = Int
type Time   = (Hour,Minute)


-- Exercise 1
--
timeToMinutes :: Time -> Minute
timeToMinutes (h,m) = 60*h + m

minutesToTime :: Minute -> Time
-- minutesToTime m = (m `div` 60,m `mod` 60)
minutesToTime m = (div m 60,mod m 60)


-- Exercise 2
--
wakeUp :: Time -> Time -> Time
wakeUp t t' = minutesToTime (timeToMinutes t - timeToMinutes t')


-- Exercise 3
--
positive :: Int -> Bool
positive x | x>=0      = True
           | otherwise = False


-- Exercise 4
--
validMinute :: Minute -> Bool
validMinute m = 0<=m && m<=59

validHour :: Minute -> Bool
validHour h = 0<=h && h<=23


-- Exercise 5
--
validTime :: Time -> Bool
validTime (h,m) = validHour h && validMinute m
