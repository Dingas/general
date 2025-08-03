;;;; lab01.lisp


(deftest test-my-abs ()
  (check
    (equal (my-abs 0) 0)
    (equal (my-abs -1) 1)
    (equal (my-abs 4) 4)))

(deftest test-largest ()
  (check
    (equal (largest 5 4) 5)
    (equal (largest 4 5) 5)
    (equal (largest 0 0) 0)
    (equal (largest -1 10) 10)
    (equal (largest 10 -10) 10)))

(deftest test-dep ()
  (check
    (equal (dep 3 4) 7)
    (equal (dep 50000 5) 50005)
    (equal (dep -50000 0) -50000)
    (equal (dep -10000 10000) nil)
    (equal (dep 10000 100000) nil)))

(deftest test-wdr ()
  (check
    (equal (wdr 20000 5) 19995)
    (equal (wdr 5 20000) 20005)
    (equal (wdr 1 1) 0)
    (equal (wdr 1 5) 6)
    (equal (wdr 20000 10000) 30000)))

(deftest test-withdraw ()
  (check
    (equal (progn
             (setf *balance* 100)
             (withdraw 30))
           100)
    (equal (progn
             (setf *balance* 100)
             (withdraw 0)
             (withdraw 20)
             (withdraw 20))
           60)
    (equal (progn
             (setf *balance* 70)
             (withdraw 60))
           10)
    (equal (progn
             (setf *balance* 10)
             (withdraw 80))
           10)
    (equal (progn
             (setf *balance* 10)
             (withdraw 10001))
           10)
    (equal (progn
             (setf *balance* 10)
             (withdraw -80))
           10)
    (equal (progn
             (setf *balance* 10)
             (withdraw -1))
           10)))

(deftest test-deposit ()
  (check
    (equal (progn
             (setf *balance* 100)
             (deposit 0)
             (deposit 50000))
           100)
    (equal (progn
             (setf *balance* 100)
             (deposit 10)
             (deposit 20))
           130)
    (equal (progn
             (setf *balance* 100)   
             (deposit -10001))
           100)
    (equal (progn
             (setf *balance* 100)   
             (deposit -1))
           100)
    (equal (progn
             (setf *balance* 100)   
             (deposit -50000))
           100)))

(defun test-lab01 ()
  (test-my-abs)
  (test-largest)
  (test-dep)
  (test-wdr)
  (test-withdraw)
  (test-deposit))

(test-lab01)
