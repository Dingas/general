defmodule Lab4 do

    def sumEven (list) do
        sumEven(list, 0, Enum.count(list))
    end
    def sumEven(list, sum, count) when count > 1 do
        if rem hd list == 0, do: sumEven(tl list, sum + hd list, count - 1), else: sumEven(tl list, sum, count - 1)
    end
    def sumEven(list, sum, count) do
        if rem hd list == 0, do: hd list + sum, else: sum
    end

    def sumNum (list) do
        sumNum(list, 0, Enum.count(list))
    end
    def sumNum(list, sum, count) when count > 1 do
        if is_integer(hd list) || is_float(hd list), do: sumNum(tl list, sum + hd list, count - 1), else: sumNum(tl list, sum, count - 1)
    end
    def sumNum(list, sum, count) when count > 1 do
        if is_integer(hd list) || is_float(hd list), do: sum + hd list, else: sum
    end

    def tailFib(n) do
        Enum.reverse(fib(n))
    end
    def fib(1), do: [0]
    def fib(2), do: [1|fib(1)]
    def fib(n) when n > 2 do
        [x, y|_] = all = fib(n-1)
        [x + y|all]
    end
end