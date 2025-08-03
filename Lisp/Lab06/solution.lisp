



(defun next-state (std x)
    (loop for i in std
        do (if (eq (car i) x) (return (cdr i)))
    )
)



(defun jump-state (std s x)

    (if (eq (next-state std x) s)
        (if (not (null (next-state std s)))
            (next-state std s))
        x);)
        
        
        
        )


(defun next-fork (std x)
    

)



(defun interleave (x y)
    (setf z (cons (car x) (car y)))
    (interleave-helper (cdr x)(cdr y) z)
)

(defun interleave-helper (x y z)
    (if (or(null x) (null y))
        (cons z (cons x y))
        (interleave-helper (cdr x) (cdr y) (cons z (cons(car x) (car y))))
    )
)

(defun comb (n k)
    
    ;(if (> n 0)
     ;   (if (or(= k 0)(= n k))
     ;   1
    ;    (comb-helper (n k 0))
   ; )
)

(defun comb-helper(n k c)
    
)