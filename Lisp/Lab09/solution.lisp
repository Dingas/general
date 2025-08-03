



(defun next-state (g x)
    (loop for i in g
        do (if (eq (car i) x) (return (cdr i)))
    )
)


(defun has-loop (g s)
    
    (setq slow (next-state g s) fast (next-state g (next-state g s)))
    
    
    (if (not(null slow))
        (if (or(eq slow fast)(eq s fast)) 
            T
            
                (has-loop g slow))
    )
    
    
)
