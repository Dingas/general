module Haha where


test = let x = 7
           y = x
           in y + x
		   
foo x = if x == 0 then "Done"
                  else foo(x-1)