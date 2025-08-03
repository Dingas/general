(defvar *DISCIPULUS-STATES* '((sleeping . eating)
                             (eating . (waiting texting blogging))
                             (texting . programming)
                             (waiting . programming)
                             (blogging . programming)
                             (programming . debugging)
                             (debugging . (watching-Utube working-out)) 
                             (watching-Utube . sleeping)
                             (working-out . sleeping)))
(defun discipulus (state)

  (setq newState (cdr (assoc 'state *discipulus-states*)))

  (if (eq state eating) (setq newState (nth (random 3)newState)))
 
  (if (eq state debugging) (setq newState (nth (random 2)newState))
      )

  newState
  )

(defun sleepless (state)

    (setq newState (cdr (assoc 'state *discipulus-states*)))

    (if (eq state eating) (setq newState (nth (random 3)newState)))
    
    (if (eq state debugging) (setq newState (nth (random 2)newState))
        )

    (if (eq newState sleeping) (setq newState eating))
    newState
  )

(defun discipulus-on-caffiene (state)

  (setq newState (cdr (assoc 'state *discipulus-states*)))

  (if (eq state eating) (setq newState (nth (random 3)newState)))
  
  (if (eq state debugging) (setq newState (nth (random 2)newState))
      )

  (discipulus newState)
  )

  
  
  
  
  
  
  

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;





(defun my-append (x y)
    (if (null x)
        y
        (cons (car x) (concat-lists (cdr x) y)))
)



(defun power(x y)
(if (eq y 0) 1 ( * x (power x (- y 1)) ) )
)


(defun comb (n k)
  (if (or (< n k) (< k 0))
    NIL
    (comb-helper n k 1))
)

(defun comb-helper (n k acc)
  (if (or (= k 0) (= n k))
    acc
    (comb-helper (- n 1) (- k 1) (* acc (/ n k))))
 )
