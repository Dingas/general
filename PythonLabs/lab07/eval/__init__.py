class BinaryTree:
    def __init__(self,rootObj):
        self.key = rootObj
        self.leftChild = None
        self.rightChild = None

    def insertLeft(self,newNode):
        if self.leftChild == None:
            self.leftChild = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.leftChild = self.leftChild
            self.leftChild = t

    def insertRight(self,newNode):
        if self.rightChild == None:
            self.rightChild = BinaryTree(newNode)
        else:
            t = BinaryTree(newNode)
            t.rightChild = self.rightChild
            self.rightChild = t


    def getRightChild(self):
        return self.rightChild

    def getLeftChild(self):
        return self.leftChild

    def setRootVal(self,obj):
        self.key = obj

    def getRootVal(self):
        return self.key


                
def evalTree(tree, environment):
    
    def evalVar(var, environment)
        for x in range(environment):
            x = 
    
    def calc(val1,val2,op):
    if op == '*':
        return val1 * val2
    elif op == '/':
        return val1 / val2
    elif op == '+':
        return val1 + val2
    elif op == '-':
        return val1 - val2
    
    if type(root) == int:
        expression = root
        value = expression
        return value
    else:
        if root == * or root == / or root == + or root == -:
            def evalCalc(tree, root, environment):
                left = getFirstChild(root)
                right = getfirstChild(root)
                if left == * or left == / or left == + or left == -:
                    evalCalc(tree,left,environment)
                else:
                    if right == * or right == / or right == + or right == -:
                        evalCalc(tree,right,environment)
                    else:
                        right = evalVar(right,environment)
                        left = evalVar(left,environment)
                    
                
                
                if type(left) == int and type(right) == int:
                    setRootVal(getRootVal(root), calc(left, right, getRootVal(root))
                    if root == tree[0]
                        value = root
                        return value
                
                    
            
            for x in range(len(tree)):
                if tree[x] == *:
                    if getFirstChild(x) == 
                    value = getFirstChild(x) * getSecondChild(x)
            
        else:
            value = evalVar(root,environment)
            return value
            
              
    
    """
    for x in range(len(tree)):
        if tree[x] == *:
            if getFirstChild(x) == 
            value = getFirstChild(x) * getSecondChild(x)
            
    for x in range(len(tree)):
        if getRootVal(x) == /:
            if tree(x).getSecondChild() == 0:
                return None
            else:
                value = tree(x).getFirstChild() / tree(x).getSecondChild()
            if tree(x) == +:
                value = tree(x).getFirstChild() + tree(x).getSecondChild()
                if tree(x) == -:
                    value = tree(x).getFirstChild() - tree(x).getSecondChild()
                        
            
        print(tree[x])
    

    root=getRootVal(tree)

                               
    
    print(root)
    insertFirst[root,'q']
    
    print(getFirstChild(root))
    

myTree = ['a', ['b', ['d',[],[]], ['e',[],[]] ], ['c', ['f',[],[]], []] ]
evalTree(myTree,0)
print(myTree)