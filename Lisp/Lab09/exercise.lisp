(defstruct (tr-node (:conc-name nil))
  val
  (children (list)))

(defun tr-lookup (key root)
  (dotimes (i (length key) (val root));; when iteration terminates normally
    ;; we have found the node we were looking for
    (let ((ch (aref key i)))
      (rtl:if-it (cdr (assoc ch (children root)))
                 (setf root rtl:it)
                 (return)))))


(defun tr-add (key val root)
  (let ((i 0))
    (rtl:dovec (ch key) ; traverses the trie checking if part of key is in it
               (let ((it (cdr (assoc ch (children root)))))
                 (if it 
                     (setf root it
                           i (1+ i))
                     (return))))
    (if (and (val root) (= i (length key)))
        ;; something has already being stored at key -
        ;; so we signal a continuable error that 
        ;; gives the user two options: overwrite or abort
        (cerror "Assign a new value"
                "There was already a value at key: ~A" (val root))
        (rtl:dovec (ch (subseq key i)) ;(rtl:slice key i))
                   (let ((child (make-tr-node)))
                     (push (cons ch child) (children root))
                     (setf root child))))
    (setf (val root) val)))

(defun tr-equal? (t1 t2) ;; To be used in unit testing
  (defun children-equal? (c1 c2)
    (or (and (null c1) (null c2))
        (let* ((a1 (car c1)) (a2 (car c2))
               (d1 (car a1)) (d2 (car a2))
               (s1 (cdr a1)) (s2 (cdr a2)))
          (and (equal d1 d2)
               (tr-equal? s1 s2)
               (children-equal? (cdr c1) (cdr c2))))))
  (and (equal (type-of t1) 'tr-node)
       (equal (type-of t2) 'tr-node)
       (eql (val t1) (val t2))
       (children-equal? (children t1) (children t2))))   


(defun tr-delete (key root)


  )

(defun tr-count (root)


  )
