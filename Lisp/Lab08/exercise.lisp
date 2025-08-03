(defun evaluate (e env)
  (let ((res (valid-args? e)))
    (if (car res)
        (if (atom e)
            (cond
              ((constant? e) e)
              ((symbol? e) (lookup e env))
              ((or (procedure? e) (numberp e)) e)
              (t (wrong "Could not evaluate expression: ~S~%" e)))
            (case (car e)
              ((progn) (eprogn (cdr e) env))
              
              ((if) (if? (cdr e) env))
              ((let) (let? (cdr e) env))
              
              
              ((setf) (update! (cadr e) env (evaluate (caddr e) env)))
              (t (invoke (evaluate (car e) env) (evlist (cdr e) env)))))
        (format t "Invalid number of args: expected ~d, got ~d in ~S~%" (caddr res) (cadr res) e))))

(defun lookup (e env)
  (let ((v (assoc e env)))
    (if v (cdr v)
        (wrong "Unbound-variable: ~S~%" e))))

(defun update! (var env value)
  (let ((kv (assoc var env)))
    (setf (cdr kv) value)))

(defun eprogn (el env)
  (let ((result (evaluate (car el) env)))
    (dolist (e (cdr el) result)
      (setf result (evaluate e env)))))

(defun if? (el env)
  (setf test (lookup (car el) env))
  (setf then (lookup (cadr el) env))
  (setf else (caddr el))

  (if (test)
      (then)
      (else))
  )


(defun let? (el env)
  (dolist (e (el) )
    (setf (car e) (cdr e))
    )
  (progn env)
  )

(defun procedure? (fn)
  (or (eql fn '+)
      (eql fn '-)
      (eql fn '*)
      (eql fn '/)))

(defun wrong (m &optional v)
  (format t m v))

(defun check-arg-types (fn args)
  (and (procedure? fn)
       (numberp (first args))
       (numberp (second args))))

(defun invoke (fn args)
  (if (check-arg-types fn args)
      (apply fn args)
      (format t "Invalid function ~S or invalid parameter types ~a" fn args)))    

(defun invoke (fn args)
  (if (procedure? fn)
      (apply fn args)
      (wrong "Could not evaluate function: ~S" fn)))

(defun evlist (lis env)
  (when lis
    (let ((a (evaluate (car lis) env)))
      (cons a (evlist (cdr lis) env)))))

(defun constant? (s)
  (or (eql s 'nil)
      (eql s 't)
      (stringp s)))

(defun symbol? (s)
  (and (symbolp s) (not (procedure? s)) (not (constant? s))))

(defun valid-args-num? (lst num)
  (let* ((len (length lst)) (res (= len num)))
    (list res len num)))

(defun valid-args? (lst)
  (if (eql (type-of lst) 'cons)
      (case (car lst)
        ((setf) (valid-args-num? lst 3))
        ((if) (valid-args-num? lst 4))
        ((let)
         (progn
           (loop for item in (cadr lst) do
                 (let ((res (valid-args-num? item 2)))
                   (if (not (car res))
                       (return-from valid-args? (list nil (cadr res) 2)))))
           '(t 2 2)))
        (t (let ((len (length lst)))
             (list t len len))))
      '(t 0 0)))













(defun test-if()
  (and
   (equal (evaluate '(if x y x) (list (cons 'x nil) (cons 'y 1))) nil)
   (equal (evaluate '(progn
                      (setf x 1)
                      (if x (setf x (+ x y)) 
                          x))
                    (list (cons 'x  nil) (cons 'y  1)))
          2)))

(defun test-let ()
  (and
   (equal (evaluate '(let ((x 1) (y 2)) (+ x y)) nil) 3)
   (equal (evaluate '(let ((x (let ((x 2)) (* x 2)))) x) nil) 4)
   (equal (evaluate '(let ((x (* y 2))) (setf y (+ x 2)) (+ x y)) (list (cons 'y  3))) 14)))

(defun main ()
  (test-if)
  (test-let))
