module Cauchy where

data CauchyList = CauchyList Int [Int]

instance Eq CauchyList where
  (CauchyList x1 y1) == (CauchyList x2 y2) = (x1==x2 && y1==y2)
  (CauchyList x1 y1) /= (CauchyList x2 y2) = not (x1==x2 && y1==y2)
    
mul(p, a, b)= do
  let len1 = length(a)
  let len2 = length(b)
  let len = (len1+len2)-1
  let finalOut = [ foldr(+) 0 [do (helper(a,i) * helper(b,x-i)) | i <- [0 .. x]] | x <- [0 .. len-1] ]
  let finalfinalOutput = CauchyList p (map (`mod` p) finalOut)
  finalfinalOutput

helper(list,x) = do
  if ( x < length(list) ) then list!!x 
  else 0
	
instance Num CauchyList where
    
  (CauchyList p a) * (CauchyList p b) = (mul (p, a, b))
        		  
	  --fromInteger n = let y = (fromInteger n) in CauchyList x y
    
instance Show CauchyList where
  show (CauchyList p xs) = (filter(/='"') ("p:" ++ show p ++"\nlength:" ++ show (length xs) ++ "\ncontent:" ++ show xs))

--take diff (repeat 0)







