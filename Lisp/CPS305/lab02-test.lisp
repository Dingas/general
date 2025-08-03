;; Test cases

(deftest test-sigma ()
  (check
    (equal (sigma #'(lambda (x) x) 0 3) 6)
    (equal (sigma #'(lambda (x) (* x x)) 0 3) 14)
    (equal (sigma #'(lambda (x) (* x x)) 3 6) 86)))

(deftest test-my-function ()
  (check
    (equal (my-function #'(lambda (x) (+ (* 3 x x) 4.7))) 7.7)
    (equal (my-function #'(lambda (x) x)) 1)
    (equal (my-function #'(lambda (x) (* x x))) 1)
    (equal (my-function #'(lambda (x) (+ x x))) 2)))

(deftest test-sum-odd ()
  (check
    (equal (sum-odd 1 5) 9)
    (equal (sum-odd 2 5) 8)
    (equal (sum-odd 0 1) 1)
    (equal (sum-odd 2 2) 0)
    (equal (sum-odd 1 1) 1)))

(deftest test-a-sum ()
  (check
    (equal (a-sum 0 3) 6)
    (equal (a-sum 1 1) 1)
    (equal (a-sum 1 0) 0)
    (equal (a-sum 2 4) 9)))

(defun test-lab02 ()
  (test-sigma)
  (test-my-function)
  (test-sum-odd)
  (test-a-sum))

