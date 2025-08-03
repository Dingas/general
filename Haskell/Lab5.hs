module Lab5 where

thirdLast :: [a] -> a

everyOther :: [a] -> [a]

sumPosList :: (Num p, Ord p) -> [p] -> p


thirdLast xs = head (drop ((length xs)-3) xs)

everyOther xs = map fst $ filter (odd . snd) $ zip xs [1..]

sumPosList = sum (map abs xs)