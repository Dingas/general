import unittest

class HashTest(unittest.TestCase):

    def test_put(self):
    
        self.assertEqual('foo'.upper(), 'FOO')

if __name__ == '__main__':
    unittest.main()