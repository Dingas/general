import unittest

from mySolution import infixToPostfixEval

class TestInfixToPostFixEval(unittest.TestCase):
    def test_single_operand(self):
        """
        Test an expression containing a single operand
        """
        exp = "4"
        pexp, value = infixToPostfixEval(exp)
        self.assertEqual(pexp, "4")
        self.assertEqual(value, 4)
    def test_single_paren_operand(self):
        """
        Test  an expression containing a single parenthesized operand
        """
        exp = "( 4 )"
        pexp, value = infixToPostfixEval(exp)
        self.assertEqual(pexp, "4")
        self.assertEqual(value, 4)
    def test_paren_exp(self):
        """
        Test  an expression with parenthesis
        """
        exp = "8 / ( 4 - 2 )"
        pexp, value = infixToPostfixEval(exp)
        self.assertEqual(pexp, "8 4 2 - /")
        self.assertEqual(value, 4)
    def test_factorial(self):
        """
        Test  an parenthesized factrial parenthesis
        """
        exp = "3 ! !"
        pexp, value = infixToPostfixEval(exp)
        self.assertEqual(pexp, "3 ! !")
        self.assertEqual(value, 720)
    def test_general(self):
        """
        Test  an expression with other operators
        """
        exp = "4 * ( 3 - 2 / 6 ) + ( 8 / 2 ) !"
        pexp, value = infixToPostfixEval(exp)
        self.assertEqual(pexp, "4 3 2 6 / - * 8 2 / ! +")
        self.assertEqual(value, 34.666666666666664)

if __name__ == '__main__':
    unittest.main()
