module Poker where

values = take 52 (cycle [1..13])
suits = replicate 13 "C" ++ replicate 13 "D" ++ replicate 13 "H" ++ replicate 13 "S"
cards = zip values suits
deck = zip cards [1..52]

getCard x = deck !! (x - 1)

getIndex x xs = head $ filter ((== x) . (xs !!)) [0..]

getValues xs = map fst $ map fst xs

getValue x = fst $ fst x

getTValues xs = map snd xs

getTValue x = snd x

getSuit x = snd $ fst $ x

------------
------------

remove :: Int -> [a] -> [a]
remove n xs = do
  if n == length xs
  then take ((length xs)-1) xs
  else if n == 0
    then tail xs
    else do
         let (ys,zs) = splitAt n xs 
         ys ++ (tail zs)
         
insert n x xs = do
    if n == length xs
      then take ((length xs)-1) xs ++ x
      else if n == 0
        then x ++ tail xs
        else do
             let (ys,zs) = splitAt n xs 
             ys ++ (tail zs)

removeElement x xs = remove (getIndex x xs) xs

--

sameSuit x y = do
    if (getSuit x) == (getSuit y)
    then True
    else False
    
sameVal x y = do
    if (getValue x) == (getValue y)
    then True
    else False
    
escalatingVal x y = do
    if (getValue x) == ((getValue y)-1)
    then True
    else False

greaterVal x y = do
    if (getValue x) > (getValue y)
    then True
    else False
    

greaterTVal x y = do
    if (getTValue x) > (getTValue y)
    then True
    else False

greaterCard x y = do
    if sameVal x y
    then if greaterTVal x y
         then True
         else False
    else if greaterVal x y
         then True
         else False
         
         
--------------
--------------




getHighCard x y = do
    if sameVal x y
    then if greaterTVal x y
         then x
         else y
    else if greaterVal x y
         then x
         else y

getLowCard x y = do
    if sameVal x y
    then if greaterTVal x y
         then y
         else x
    else if greaterVal x y
         then y
         else x
         
--finds first match from LEFT 
getAnyMatchL xs = do
    if sameVal (head xs) (head $ tail xs)
    then head xs
    else getAnyMatchL (tail xs)
    
    
--finds first match from RIGHT
getAnyMatchR xs = do
    if sameVal (last xs) (last (init xs))
    then last xs
    else getAnyMatchR (init xs)
------------
------------

handRank xs = do

    if isRoyalFlush xs
    then 9
    else if isStraightFlush xs
         then 8
         else if is4s xs
              then 7
              else if isFullHouse xs
                   then 6
                   else if isFlush xs
                        then 5
                        else if isStraight xs
                             then 4
                             else if is3s xs
                                  then 3
                                  else if is22s xs
                                       then 2
                                       else if is2s xs
                                            then 1
                                            else 0
              

bestHand xs ys = do
    let rank1 = handRank xs
    let rank2 = handRank ys
    if rank1 > rank2
    then xs
    else if rank2 > rank1
         then ys
         else tieBreaker xs ys rank1


-- used for 4s and 2s
getKicker xs x = do
    if sameVal (last xs) x
    then getKicker (init xs) x
    else last xs


is4sTBHelper xs = do
    if allMatch (init xs)
    then head xs
    else head (tail xs)

is4sTB xs ys = do
    let x = is4sTBHelper xs
    let y = is4sTBHelper ys
    if sameVal x y
    then if greaterVal(getKicker xs x) (getKicker ys y)
         then xs
         else ys
         else if greaterVal x y
              then xs
              else ys
    


-- fullhouse tiebreaker also used for 3s
isFullHouseTBHelper xs = do
    let x = xs !! 2
    if sameVal x (xs !! 1)
    then xs !! 4
    else xs !! 1
isFullHouseTB xs ys = do
    let x = isFullHouseTBHelper xs
    let y = isFullHouseTBHelper ys
    if sameVal (xs !! 2) (ys !! 2)
    then if greaterVal x y
         then xs
         else ys
         else if greaterVal x y
              then xs
              else ys
    
    
--also used for straight tiebreaker
isFlushTB xs ys = do
    if sameVal (last xs) (last ys)
    then if greaterTVal (last xs) (last ys)
         then xs
         else ys
         else if greaterVal (last xs) (last ys)
              then xs
              else ys

is22sTB xs ys = do
    if sameVal (getAnyMatchR xs) (getAnyMatchR ys)
    then if greaterVal (getAnyMatchL xs) (getAnyMatchL ys)
         then xs
         else ys
         else if greaterVal (getAnyMatchR xs) (getAnyMatchR ys)
              then xs
              else ys

is2sTB xs ys = do
    let x = getAnyMatchR xs
    let y = getAnyMatchR ys
    if sameVal x y
    then if greaterCard (getKicker xs x) (getKicker ys y)
         then xs
         else ys
         else if greaterCard x y
              then xs
              else ys

highCardTB xs ys = do
    if sameVal (last xs) (last ys)
    then if greaterCard (last (init xs)) (last (init xs))
         then xs
         else ys
         else if greaterCard (last xs) (last ys)
              then xs
              else ys

tieBreaker xs ys rank = do
    if rank == 8
    then if greaterCard (last xs) (last ys)
         then xs
         else ys
         else if rank == 7
              then is4sTB xs ys
              else if rank == 6
                   then isFullHouseTB xs ys 
                   else if rank == 5
                        then isFlushTB xs ys
                        else if rank == 4
                             then isFlushTB xs ys -- straight shares flush tiebreaker
                             else if rank == 3
                                  then isFullHouseTB xs ys -- 3s shares fullhouse tiebreaker
                                  else if rank == 2
                                       then is22sTB xs ys
                                       else if rank == 1
                                            then is2sTB xs ys
                                            else xs
                             





{--}



-------------
-------------

flushHelper xs suit = do
    if length xs == 1
    then if suit == getSuit (head xs)
         then True
         else False
    else if sameSuit (head xs) (head $ tail xs)
         then flushHelper (tail xs) (getSuit $ head xs)
         else False
isFlush xs = flushHelper xs "X"
--
isRoyalFlush xs = do
    if isFlush xs
    then if getValue (head xs) == 1 && getValue (xs !! 1) == 10
         then if isStraight (tail xs)
              then True
              else False
         else False
    else False
    
isStraightFlush xs = do
    if isFlush xs && isStraight xs
    then True
    else False

isStraight xs = do
    if length xs == 2
    then if escalatingVal (head xs) (head $ tail xs)
         then True
         else False
    else if escalatingVal (head xs) (head $ tail xs)
         then isStraight (tail xs)
         else False

allMatch xs = do
    if sameVal (head xs) (head $ tail xs)
    then if (length xs == 2)
         then True
         else allMatch (tail xs)
    else False
    
anyMatch xs = do
    if sameVal (head xs) (head $ tail xs)
    then True
    else if length xs > 2
         then anyMatch (tail xs)
         else False
         
allSuitMatch xs = do
    if sameSuit (head xs) (head $ tail xs)
    then if (length xs == 2)
         then True
         else allSuitMatch (tail xs)
    else False
         
is4s xs = do
    if allMatch (init xs)
    then True
    else if allMatch (tail xs)
         then True
         else False

isFullHouse xs = do
    if (sameVal (head xs) (head $ tail xs) && allMatch (drop 2 xs)) || (allMatch (take 3 xs) && sameVal (head $ drop 3 xs) (last xs))
    then True
    else False
    
is3s xs = do
    if allMatch (take 3 xs) || allMatch (tail $ take 4 xs) || allMatch (drop 2 xs)
    then True
    else False

is22s xs = do
    if (sameVal (head xs) (head $ tail xs) && sameVal (xs !! 2) (xs !! 3)) || (sameVal (head xs) (head $ tail xs) && sameVal (xs !! 3) (xs !! 4)) || (sameVal (xs !! 1) (xs !! 2) && sameVal (xs !! 3) (xs !! 4))
    then True
    else False
    
is2s xs = anyMatch xs

-------------------
-------------------

minHelper minCard xs = do
    if (length xs == 1)
    then minCard
    else minHelper (getLowCard minCard (head xs)) (tail xs)
         
      

getMin xs = minHelper ((14,"X"),53) xs


cardSortHelper xs i = do
    if i == 4
    then if getLowCard (xs !! 3) (xs !! 4) == xs !! 3
         then xs
         else take 3 xs ++ reverse (drop 3 xs)
    else do
       let ys = drop i xs
       let minCard = getMin ys
       let minIndex = getIndex minCard ys
       let zs = remove minIndex ys
       cardSortHelper ((take i xs) ++ (take 1 (repeat minCard)) ++ zs) (i+1)
       
           
            
cardSort xs = cardSortHelper xs 0
    
  {-          
  -}


getHand hole river = handBuilder (hole ++ river) river 6

handBuilder xs best i = do
    let hand = handBuilderHelper xs best i (i-1)
    if i == 1
    then hand
    else handBuilder xs hand (i-1)

handBuilderHelper xs best i n = do
    let x1 = remove i xs
    let x2 = remove n x1
    let hand = cardSort x2
    let newBest = bestHand best hand
    if n == 0
    then newBest
    else handBuilderHelper xs newBest i (n-1)
    
    
------------------
------------------

deal xs = do
  let cards = map getCard xs
  let hole1 = [head cards, cards !! 2]
  let hole2 = [head (tail cards), cards !! 3]
  let river = cardSort(drop 4 cards)
  
  let hand1 = getHand hole1 river
  let hand2 = getHand hole2 river
  
  bestHand hand1 hand2
{-
((2,"D"),15)
fst $ -> (2,"D")
fst $ fst $ head x -> 2
snd $ head x -> 15
snd $ fst $ head x -> "D"
-}
--C 1-13
--D 14-26
--H 27-39
--S 40-52