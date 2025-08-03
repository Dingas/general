module Cauchy where

    data CauchyList = CauchyList { p :: Int, content :: [Int]}

    instance Eq CauchyList where
      (CauchyList x1 y1) == (CauchyList x2 y2) = (x1==x2 && y1==y2)
      (CauchyList x1 y1) /= (CauchyList x2 y2) = not (x1==x2 && y1==y2)
      
    add a b p = do
      let diff = (length a) - (length b)
      if (diff > 0)
        then CauchyList p (map (`mod` p) (zipWith (+) a b ++ (take diff (repeat 0))))
        else CauchyList p (map (`mod` p) (zipWith (+) b a ++ (take (abs diff) (repeat 0))))
        
    sub a b p = do
      let diff = (length a) - (length b)
      if (diff > 0)
        then CauchyList p (map (`mod` p) (zipWith (-) a b ++ (take diff (repeat 0))))
        else CauchyList p (map (`mod` p) (zipWith (-) b a ++ (take (abs diff) (repeat 0))))
      
    mul a b p = do
      let len1 = length(a)
      let len2 = length(b)
      let len = (len1+len2)-1
      let c = [ foldr(+) 0 [do (helper(a,i) * helper(b,x-i)) | i <- [0 .. x]] | x <- [0 .. len-1] ]
      let output = CauchyList p (map (`mod` p) c)
      output
    
    helper(list,x) = do
      if ( x < length(list) ) then list!!x 
      else 0
    
    
    instance Num CauchyList where
    
      (CauchyList p1 a) + (CauchyList p2 b) = add a b p1
      (CauchyList p1 a) - (CauchyList p2 b) = sub a b p1
      (CauchyList p1 a) * (CauchyList p2 b) = mul a b p1
      abs (CauchyList p1 a) = CauchyList (abs p1) (map abs a)
      signum (CauchyList p1 a) = CauchyList (signum p1) (map signum a)
      fromInteger n = let a = [(fromInteger n)] in CauchyList 0 a
    
    instance Show CauchyList where
      show (CauchyList p content) = (filter(/='"') ("p:" ++ show p ++ "\nlength:" ++ show (length content) ++ "\ncontent:" ++ show content))