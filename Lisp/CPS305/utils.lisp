;;;; utils.lisp

(defvar *results* nil)

(defvar *test-name* nil)

(defvar *test-cases* nil)

;; Maximum running time (in seconds) allotted to the
;; evaluation of a test case. Once that time expires, the respective
;; thread is terminated, and a fail is associated to the respective
;; test case 

(defvar *max-time* 5) 

(defvar *runtime-error* nil)

(defun report-result (result form)
  (let ((res (not (or (eq result 'runtime-error)
		      (typep result 'condition)
		      (not result)))))
    (push (list res result (car *test-name*) form) *results*)
    ;; (format t "~:[FAIL~;pass~] ...~a: ~a~%" result *test-name* form)
    res))

(defmacro with-gensyms ((&rest names) &body body)
  `(let ,(loop for n in names collect `(,n (gensym)))
     ,@body))

(defmacro combine-results (&body forms)
  (with-gensyms (result)
    `(let ((,result t))
       ,@(loop for f in forms collect `(unless ,f (setf ,result nil)))
       ,result)))

;; Added to handle detection of endless loop when evaluating test cases
(defmacro time-execution  (expr maxtime)
  "Evaluates expr in a separate thread. 
   If expr's execution time reaches maxtime seconds, then kills the thread and
   pushes the expression that ran out of execution time in *RUNTIME-ERROR*
   then returns *RUNTIME-ERROR*. Otherwise returns the result of evaluating expr."
  (let ((thread (gensym))
	(keep-time (gensym))
	(stime (gensym))
	(res (gensym)))
    `(let* ((,res nil)
	    (,thread (sb-thread:make-thread 
		     (lambda () (setf ,res ,expr)))))
       (labels ((,keep-time (,stime)
		  (cond ((and (> (/ (- (get-internal-real-time) ,stime) 
				    internal-time-units-per-second)
				 ,maxtime)
			      (sb-thread:thread-alive-p ,thread))
			 (progn
			   (sb-thread:terminate-thread ,thread)
			   (push ',(cadr expr) *runtime-error*)
			   (setf ,res 'runtime-error)))
			 ((sb-thread:thread-alive-p ,thread) (,keep-time ,stime))
			 (t ,res))))
	 (,keep-time (get-internal-real-time))))))


(defmacro check (&body forms)
  `(combine-results
     ,@(loop for f in forms collect
	     `(report-result (time-execution
			      (handler-case ,f
				(error (condition)
				  (push condition *runtime-error*)
				  condition))
			      ,*max-time*) ',f))))

(defmacro deftest (name parameters &body body)
  `(defun ,name ,parameters
     (push (list ',name ',body) *test-cases*)
     (let ((*test-name* (append *test-name* (list ',name))))
       ,@body)))



(defun calc-mark (res ws)
  "Calculates student mark based on the results (res) from running the test 
cases and on the weight associated to each function. If ws is nil then
the mark is calculated as the # of passes divided by the total # of cases.
- ws is a list of pairs (<function-name> <weight>) Note: sum of weights must be 100
- res is the list stored in the global variable *results*"
  (labels ((get-avg (fn res accumPass accumT)
	     (dolist (x res (if (zerop accumT)
				(error "Test function ~S not defined in unit test" fn)
				(/ accumPass accumT)))
	       (when (equal fn (caddr x))
		 (if (car x)
		     (progn (incf accumPass)
			    (incf accumT))
		     (incf accumT))))))
    (if (null ws)
	(loop for r in res
	      when (car r)
              sum 1 into c
	      finally (return (* (/ c (length res)) 100)))
	(loop for w in ws 
	      sum (* (cadr w) (get-avg (car w) res 0 0))))))

(defun run-tests (lab)
  (case lab
    (:lab01 (test-lab01))
    (:lab02 (test-lab02))
    (:lab03 (test-lab03))
    (:lab04 (test-lab04))
    (:lab05 (test-lab05))
    (:lab06 (test-lab06))
    (:lab07 (test-lab07))
    (:lab08 (test-lab08))
    (:lab09 (test-lab09))
    (otherwise (format t "Invalid lab identifier. Lab identifiers are in the form :labXX, where XX is the lab number, e.g., :lab03."))))

(defun test-lab-solution (student-solution lab)
  "Tests the student-solution lisp program using the unit-test associated with the lab key.
Lab keys are of the form ':labXX', where XX is the lab number. E.g., :lab01"
  (let ((description "No runtime errors")
        (load-error nil))
    (setf *results* nil)
    (setf *runtime-error* nil)
    (format t "~%Loading your solution...")
    (handler-case (load student-solution)
      (error (condition)
        (push condition load-error)))
    (format t "Done.~%Running test cases...")
    (run-tests lab)
    (format t "Done.~%Preparing report...Done.~%~%Report: ")
    (format t "Your solution passed ~f% of the test cases.~%~a~%~a"
            (calc-mark *results* nil)
            (cond (*runtime-error* (setf description "Runtime error")
                                   'runtime-error)
                  (load-error (setf description "Load/Compiling error")
                              'load-error)
                  (t "No runtime/load/compiling error"))
            (if (or *runtime-error* load-error)
                (setf description (concatenate 'string
                                               description
                                               (format nil "(s) when evaluating the following expressions:~%~{- ~A~%~}" (reverse *runtime-error*))))
                ""))
    (dolist (res *results*)
      (let ((pf (first res))
            (ertype (second res))
            (a (fourth res)))
        (format t "~:[FAILED~;Passed~] the assertion: ~S ~a~%" pf a (if (equal ertype 'runtime-error) ertype ""))))))

(defun pprint-test-cases (tcs)
  (when tcs
    (let* ((pair (car tcs))
           (tname (car pair))
           (bdy (cadr pair)))
      (format t "Test-case name: ~a~%" tname)
      (pprint-tc-bdy bdy))
    (pprint-test-cases (cdr tcs))))

(defun pprint-assertions (al)
  (when al
    (let ((a (car al)))
      (cond ((= (length a) 3) (format t "    ~S should return ==> ~a~%" (second a) (third a)))
            ((eql (car a) 'not) (format t "    ~S should return ==> NIL~%" (second a)))
            (t (format t "    ~S should return ==> T~%" (car a)))))
    (pprint-assertions (cdr al))))

(defun pprint-bindings (b)
  (format t "  Initial bindings:~%    ~S~%" b))

(defun pprint-tc-bdy (bdy)
  (when bdy
    (let ((expr (car bdy)))
      (cond ((eql (car expr) 'check) (format t "  Assertions: ~%")
             (pprint-assertions (cdr expr)))
            ((eql (car expr) 'let) (pprint-bindings (cadr expr))
             (pprint-tc-bdy (cddr expr)))
            (t (pprint-bindings expr))))
    (pprint-tc-bdy (cdr bdy))))
            
(defun show-test-cases (lab &optional (function nil))
  "Pretty prints the test cases associated with lab key and the function"
  (setf *test-cases* nil)
  (run-tests lab)
  (if function
      (let ((tc (find function *test-cases* :key #'car)))
        (if tc (pprint-test-cases (list tc)) (format t "Could not find ~a~%" function)))
      (pprint-test-cases *test-cases*)))

  
  
