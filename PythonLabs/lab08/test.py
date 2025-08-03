import unittest

from parsers import parse


class parse(unittest.TestCase):
    
    def test_1(self):
        """
        Test a tree containing brackets
        """
        treeP = [['5', '-', '2'], '/', '6']
        parsedTree = parse(treeP)
        self.assertEqual(parsedTree, "['/', ['-', ['5', [], []], ['2', [], []]], ['6', [], []]]")
        
    def test_2(self):
        """
        Test a tree containing a factorial
        """
        treeP = ['3', '!']
        parsedTree = parse(treeP)
        self.assertEqual(parsedTree, "	['!', [3, [], []], []]")
    
    def test_3(self):
        """
        Test a tree containing a factorial and another operator
        """
        treeP = ['5', '-', ['3', '!']]
        parsedTree = parse(treeP)
        self.assertEqual(parsedTree, "['-', ['5', [], []], ['!', ['3', [], []], []]]")
        
    def test_4(self):
        """
        Test a tree containing a factorial and brackets
        """
        treeP = ['5', '-', [['3', '-', '2'], '!']]
        parsedTree = parse(treeP)
        self.assertEqual(parsedTree, "['-', ['5', [], []], ['!', ['-', ['3', [], []], ['2', [], []]], []]]")
        
    def test_5(self):
        """
        Test a tree containing a factorial and multiple operators
        """
        treeP = ['2','*',['7', '!'],'+', '1']
        parsedTree = parse(treeP)
        self.assertEqual(parsedTree, "['+', ['*', ['2', [], []], ['!', ['7', [], []], []]], ['1', [], []]]")


if __name__ == '__main__':
    unittest.main()
