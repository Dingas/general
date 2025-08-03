;; Functions

(defvar *balance* 100)

(defun withdraw (amount)
    (if (>= *balance* amount)
        (progn
            (:= *balance* (- *balance* amount))
            *balance*)
        (format t "Insufficient funds~%")))
    (if (>= 10000 amount)
        (progn
            (:= *balance* (- *balance* amount))
            *balance*)
        (format t "Withdrawl exceeds limit~%")))
    
        
(defun deposit (amount)
    (if (>= 10000 amount)
        (progn
            (:= *balance* (+ *balance* amount))
            *balance*)
        (format t "Deposit exceeds limit~%")))
    (if (< 0 amount)
        (progn
            (:= *balance* (+ *balance* amount))
            *balance*)
        (format t "Deposit must be greater than zero~%")))
;; Test cases

(deftest test-withdraw ()
  (:= *balance* 100)
  (check
    (equal (withdraw 0) 100)
    (equal (withdraw 10) 90)
    (equal (withdraw 20) 70)
    (not (withdraw -20))
    (not (withdraw 10001))
    (not (withdraw 80))
    (equal (withdraw 60) 10)))

(deftest test-deposit ()
  (:= *balance* 100)
  (check
    (equal (deposit 0) 100)
    (not (deposit 10001))
    (not (deposit -20))
    (equal (deposit 10) 110)
    (equal (deposit 20) 130)))

(defun main ()
    (test-withdraw)
    (test-deposit))