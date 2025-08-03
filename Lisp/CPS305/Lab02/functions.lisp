
(defun dna-count (sequence)
    (setf ng 0)
    (setf na 0)
    (setf nc 0)
    (setf nt 0)
    (setq gene (string-downcase sequence))
    (loop for c across gene
        (case c
        ("g" (incf ng))
        ("a" (incf na))
        ("c" (incf nc))
        ("t" (incf nt)))
    )
    (list ng na nc nt)
    
)

(defun gc-ratio (sequence)
    (setf gene (dna-count sequence)
    (setf GC (+(nth 0 gene) (nth 2 gene)))
    (/ GC (length gene))
)


(defun divides? (a b)
    (= (rem b a) 0)) ; calculates the remainder of b/a and checks if it is zero.

(defun square (x) (* x x))

(defun find-divisor (n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? test-divisor n) test-divisor)
        (t (find-divisor n (+ test-divisor 1)))))

(defun smallest-divisor (n)
  (find-divisor n 2))

 (defun prime? (n)
    (= n (smallest-divisor n)))
    
(defun next-prime (n)
    (incf n)
    (loop while (not (prime? n))
        (incf n)
    )
)