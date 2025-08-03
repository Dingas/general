
(defun add-3 (x)
  (+ x 3))
(defun square (x)
  (* x x))

(defun my-abs (x)
 (abs x)
      )

(defun largest (x y)
 (max x y)
  )

(defun dep (b a)
  (if (< a 1000)
      (+ b a)
      )
  )

  (defun wdr (b a)
    (if(and (< a 1000)(>= b a))
       (- b a)
       (+ b a))
  )


(defvar *balance* 100)





(defun withdraw (amount)
  
  (cond  ((/= (mod amount 20) 0) (print "Must be a multiple of 20"))
        ((< amount 0) (print "Negative amount"))
        ((>= amount 10000) (print "Exceeds maximum withdrawal amount"))
        ((< *balance* amount) (print "Insufficient funds"))
        (t (:= *balance* (- *balance* amount))))
  *balance*)


(defun deposit (amount)
  (cond ((< amount 0) (print "Negative amount"))
        ((>= amount 50000) (print "Exceeds maximum deposit amount"))
        (t (:= *balance* (+ *balance* amount))))
  *balance*)
