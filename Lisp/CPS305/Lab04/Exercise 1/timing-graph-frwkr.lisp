(defun tweak-text (lst)
  (when lst
    (let ((item (car lst))
	  (rest (cdr lst)))
      (if (or (eql item #\()
	      (eql item #\))
	      (eql item #\,)
	      (eql item #\:)
	      (eql item #\%))
	  (tweak-text rest)
	  (cons item (tweak-text rest))))))
	    

(defun sl-string->list (line)
  (with-input-from-string (s line)
    (loop for object = (read s nil nil)
       while object
	 collect object)))
  

(defun ml-string->list (string)
  (with-input-from-string (s string)
    (loop for line = (read-line s nil nil)
       while line
       collect (sl-string->list line))))

(defun parse-str (str)
  (ml-string->list (coerce (tweak-text (coerce str 'list))
			   'string)))

(defmacro timef (exp)
  "Returns as values the timing information that
TIME prints to *trace-output*, in the following order: 
run time, real time, % of CPU, and # of processor cycles."
  (let ((g (gensym)))
    `(let ((,g (cdr (parse-str (with-output-to-string (*trace-output*)
				 (time ,exp))))))
       (values (caadr ,g)       ; run time
	       (caar ,g)        ; real time
	       (caaddr ,g)      ; % of CPU
	       (car (cadddr ,g)))))) ; # of processor cycles
	     
(defun generate-points ()
  (with-open-file (s "output.dat" :direction :output :if-exists :supersede)
    (do* ((init 10000)
	  (incr 20000)
	  (lim 1000000)
	  (reps 1000)
	  (i init (+ i incr)))
	 ((> i lim))
      (let ((x (do ((k 0 (1+ k))
		    (a (make-array i)))
		   ((= k i) a)
		 (:= (? a k) k)))
	    (acc1 0) 
	    (acc2 0))
	(dotimes (j reps)
	  (let ((elem (random i)))
	    (:+ acc1 (timef (aref x elem)))
	    (:+ acc2 (timef (find (- elem)  x)))))
	(format s "~a ~,8F ~,8F~%" i (/ acc1 reps) (/ acc2 reps))))))

