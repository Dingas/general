def precedence(oper):
    if oper in ['+', '-']:
        return 1
    elif oper == '!':
        return 3
    else:
        return 2


def operatorp(x):
    return x in ['+', '-', '/', '*', '!']

def numberp(x):
    return not operatorp(x) 


def parse(expr):
    return parseHelper(expr, [], [])

def parseHelper(expr, operators, operands,count=0):

    print(expr)
    print(operators)
    print(operands)

    if expr == []:
        if operators == []:
            return operands[0]
        else:
            return handleOp([], operators, operands)
        
    if isinstance(expr[0],list):
        for x in expr[0]:
            if precedence(expr[0][x]) == 3:
                return expr[0].pop(x)
        for x in expr[0]:
            if numberp(expr[0][x])==false:
                return expr[0].pop(x)
        return expr[0].pop(0)
        
    
    if numberp(expr[0]):
        return parseHelper(expr[1:], operators, [[expr[0], [], []]]+operands)
    elif operators == [] or precedence(expr[0]) > precedence(operators[0]):
        return parseHelper(expr[1:], [expr[0]]+operators, operands)
    else:
        return handleOp(expr, operators, operands)

def handleOp(expr, operators, operands):
    return parseHelper(expr, operators[1:], [[operators[0], operands[1], operands[0]]]+operands[2:])

