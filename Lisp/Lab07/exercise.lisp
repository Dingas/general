(defstruct ht
  array
  (count 0))

(defun ht-create (kvs)
  (let ((rez (make-ht :array (make-array 16 :initial-element (list)))))
    (loop :for (k v) :in kvs :do
          (ht-add k v rez))
    rez))

(defvar *ht* (ht-create nil))

(defvar *deleted* '())


(defun ht-get (key ht)

  (if (not (find key *deleted*))
      (ht-getR key ht)

      )

  
  )


(defun ht-getR (key ht)
  (rtl:with ((size (length (ht-array ht)))  ; (rtl:? ht 'array) = (ht-array ht)
             (start (rem (sxhash key) size)))   ; sxhash is a lisp function: http://clhs.lisp.se/Body/f_sxhash.htm
    (do* ((count 0 (1+ count))
          (i start (rem (1+ i) size))  ; linear probing
          (item (rtl:? ht 'array start) ; (rtl:? ht 'array start) = (aref (ht-array ht) start) 
                (rtl:? ht 'array i))) ; (rtl:? ht 'array i) = (aref (ht-array ht) i)
         ((or (null item)
              (= count size)))
      (when (matcher key (car item))
        (return 
          (values (cdr item)
                  ;; the second value is an index, at which the item was found
                  ;; (also used to distinguish the value nil from not found,
                  ;; which is also represented by nil but with no second value)
                  i))))))

(defun ht-add (key val ht)
  (setq *deleted* (remove k *deleted*)
  
  (if (not (ht-get key ht))
      (ht-addR key val ht)
      )

  )


(defun ht-addR (key val ht)
  (rtl:with ((array (ht-array ht))
             (size (length array)))
    ;; flet defines a local function that has access
    ;; to the local variables defined in HT-ADD
    (flet ((add-item (k v)
             (do ((i (rem (sxhash k) size)
                     (rem (1+ i) size)))
                 ((null (rtl:? ht 'array i))
                  (setf (rtl:? ht 'array i) (cons k 5)))
               ;; this do-loop doesn't have a body
               )))
      (when (= (rtl:? ht 'count) size)  ; note: fixes error on textbook
        ;; when the backing array is full
        ;; expand it to have the length equal to the next power of 2
        (setf size (expt 2 (ceiling (log (1+ (rtl:? ht 'count)) 2))) ; note: fixes error on textbook
              (ht-array ht) (make-array size :initial-element nil))
        ;; and re-add its contents
        (rtl:dovec (item array)  ; similar to DOLIST but for arrays
          (add-item (car item) (cdr item)))) ; note: fixes error on textbook
      ;; finally, add the new item
      (incf (ht-count ht)) ; (incf (rtl:? ht 'count))
      (add-item key val))))


(defun ht-delete (key ht)
  (setf result (ht-get key ht))
  (if (not result)
      (setf result (ht-deleteR key ht))
      )
  
  result
  )


(defun ht-deleteR (key ht)
  (setf (values x i) (ht-get key ht))
  (setf result (cons x i))

  (push k *deleted*)
  
  result
  )



(defun matcher (x y)
  (if (and (typep x 'string)(typep y 'string))
      (string= x y)
      (if (and (typep x 'integer)(typep y 'integer))
          (= x y)
          
          )
      )
  )