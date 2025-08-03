module Lab6 where


    data RegularPoly = RegularPoly {n :: Int, s :: Float}
    
    polySides (RegularPoly n s) = n
    polyLength (RegularPoly n s) = s

    instance Eq RegularPoly where
        a == b = polyArea a == polyArea b
        a /= b = not (polyArea a == polyArea b)
        
    
    instance Show RegularPoly where
        show (RegularPoly n s) = (filter(/='"') ("Number of Sides: " ++ show n ++ "\nSide Length: " ++ show s))

    
    polyArea x = do
        let sides = polySides x
        let len = polyLength x
        let perimeter = (fromIntegral sides) * len
        let apothem = len / (2*(tan(180/fromIntegral sides)))
        let area = (perimeter * apothem)/2
        area
