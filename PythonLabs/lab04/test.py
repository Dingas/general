import unittest

from mySolution\__init__ import power, powerH, C


class Test(unittest.TestCase):
    def powerTest(self):

        self.assertEqual(power(8,4),4096)
        self.assertEqual(power(6,3),216)
        self.assertEqual(power(5,0),1)
        self.assertEqual(power(4,1),4)
        
    def powerHTest(self):
        
        self.assertEqual(powerH(2,4),64)
        self.assertEqual(powerH(5,1),5)
        self.assertEqual(powerH(6,3),216)
        self.assertEqual(powerH(3,0),1)
        
        
    def CTest(self):
        
        self.assertEqual(C(10,3),120)
        self.assertEqual(C(5,2),10)
        self.assertEqual(C(15,7),6435)
        self.assertEqual(C(4,4),1)
        