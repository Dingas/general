(defstruct movie
  title  director year type)

(defparameter *size* 3) 

(defvar *db* (make-array *size*  :initial-element nil))

(deftest test-add-movie ()
  (check
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (movie-title (aref *db* 0)))
	   "Test1")
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test1")))
	   NIL)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
             (let ((a (add-movie (make-movie :title "Test3"))))
               (and (equal (movie-title (aref a 0)) "Test1")
                    (equal (movie-title (aref a 1)) "Test2")
                    (equal (movie-title (aref a 2)) "Test3"))))
	   T)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (add-movie (make-movie :title "Test3")))
	   NIL)))

(deftest test-replace-movie ()
  (check
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (list (replace-movie (make-movie :title "Test2") (make-movie :title "New-test2"))
		   (movie-title (aref *db* 1))))
	   '(t "New-test2"))
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (replace-movie (make-movie :title "Test2") (make-movie :title "Test3")))
	   NIL)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (replace-movie (make-movie :title "Test2") (make-movie :title "Test3")))
	   NIL)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (replace-movie (make-movie :title "Test3") (make-movie :title "Test4")))
	   NIL)))
	     
(deftest test-delete-movie ()
  (check
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (delete-movie "Test2")
	     (movie-title (aref *db* 1)))
	   "Test3")
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (delete-movie "Test3")
	     (aref *db* 2))
           nil)
    (equal (progn
             (setf *size* 3)
             (setf *db* (make-array *size*  :initial-element nil))
             (delete-movie "Test1"))           
           nil)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
             (delete-movie "Test1")
             (aref *db* 0))
           nil)))
    
(deftest test-num-movies ()
  (check
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (delete-movie "Test1")
	     (delete-movie "Test2")
	     (num-movies))
	   1)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (add-movie (make-movie :title "Test1"))
	     (add-movie (make-movie :title "Test2"))
	     (add-movie (make-movie :title "Test3"))
	     (num-movies))
	   3)
    (equal (progn
	     (setf *size* 3)
	     (setf *db* (make-array *size*  :initial-element nil))
	     (num-movies))
	   0)))
  
(defun test-lab03 ()
  (test-num-movies)
  (test-replace-movie)
  (test-delete-movie)
  (test-add-movie))


   
	   
	     
    
