(defun arith-eval (expr)
  (

  (let ((ops ())
        (vals ())
        (op nil)
        (val nil))
    (dolist (item expr)
      (case item
        ([ ) ; do nothing
        ((+ - * / ^ SDIV MAXF FACT) (push item ops))
        (] (setf op (pop ops) val (pop vals))
           (case op
             (+ (setf val (+ val (pop vals))))
             (- (setf val (- (pop vals)  val)))
             (* (setf val (* val (pop vals))))
             (/ (setf val (/ (pop vals)  val)))
             
             (^ (setf val ( expt (pop vals) val)))
             
             (SDIV (setf val (SDIV (pop vals) (pop vals) val)))
             (MAXF (setf val (MAXF (pop vals) (pop vals) val)))
             (FACT (setf val (FACT val)))
             
             
             
             
             )
           (push val vals))
        (otherwise (push item vals))))
    (pop vals)))
    
(defun checkBrackets(expr)
    (setq expString (string expr))
    
    (loop for char across expString
    

)

    
(defun SDIV (x y z)
    (/ (- y x) z)
    )
    
(defun MAXF (x y z)
    (max x (max y z))

)

(defun FACT (x)
    (if (= x 0)
      1
      (* x (FACT (- x 1))) ) 
)