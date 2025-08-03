defmodule Lab3 do
    def firstTwo(x) do
        hd x == hd tl x
    end

    def evenSize(x) do
        rem Enum.count(x),2 == 0
    end

    def frontBack(x) do
        tl x ++ [hd x]
    end

    def nextNineNine(x) do
        [hd x] ++ [99] ++ tl x
    end

    def isCoord(x) do
        Enum.count(x) == 2 &&  (Enum.all?(x, &is_float/1) || Enum.all?(x, &is_integer/1))
    end

    def helloIfSo(x) do
        if Enum.member?(x, "Hello"), do: List.delete(x,"Hello") ++ ["Hello"], else: x ++["Hello"]
    end

end