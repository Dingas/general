import unittest

from eval import evalTree

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

def buildTree():
    r=BinaryTree('a')
    r.insertRight('c')
    r.insertLeft('b')
    r.getLeftChild().insertRight('d')
    r.getRightChild().insertLeft('e')
    return(r)


class evalTree(unittest.TestCase):
    environment = [["a", 4], ["b", 5], ["c", 8], ["i5", 80]]
    
    def test_integer(self):
        """
        Test a tree containing an integer
        """
        r=BinaryTree('12')
        value = evalTree(r,environment)
        self.assertEqual(value, 12)
        
    def test_var(self):
    """
    Test a tree containing a variable
    """
    r=BinaryTree('i5')
    value = evalTree(r,environment)
    self.assertEqual(value, 80)
    
    def test_arith1(self):
    """
    Test a tree containing arithmetic
    """
    r=BinaryTree('*')
    r.insertLeft("a")
    r.insertRight("b")
    value = evalTree(r,environment)
    self.assertEqual(value, 20)


if __name__ == '__main__':
    unittest.main()
