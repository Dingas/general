(defun a-sum (n p)
    (setq x 0)

    (loop for i from n to p
        do(:= x(+ x i))
        )
        x
)


(defun sum-odd (n p)
    (setq x 0)
    
        (loop for i from n to p 
        
        do(when (oddp i)
        (:= x(+ x i))))
        x   
)

(defun my-function (f)
    (funcall f 1)
)

(defun sigma (f n p)
    (setq x 0)

    (loop for i from n to p
        do(:= x(+ x (funcall f i)))
        )
        x
)