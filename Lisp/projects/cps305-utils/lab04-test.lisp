;; lab04-test.lisp

(defstruct movie
  title  director year type)

(defparameter *size* 3) 

(defvar *db* (make-array *size*  :initial-element nil))

(defvar *db-list* nil)

    
(deftest test-sort-title ()
  (check
    (equal (progn
             (setf *size* 4)
             (setf *db* (make-array *size*  :initial-element nil))
             (add-movie (make-movie :title "Test2" :year 1966))
             (add-movie (make-movie :title "Test1" :year 2022))
             (add-movie (make-movie :title "Test3" :year 1984))
             (let ((res (sort-title)))
               (list (movie-title (aref res 0))
		     (movie-title (aref res 1))
		     (movie-title (aref res 2)))))
             '("Test1" "Test2" "Test3"))
    (equal (progn
             (setf *size* 4)
             (setf *db* (make-array *size*  :initial-element nil))
             (sort-title))
           nil)))
  
(deftest test-sort-year ()
  (check
    (equal (progn
             (setf *size* 4)
             (setf *db* (make-array *size*  :initial-element nil))
             (add-movie (make-movie :title "Test2" :year 1966))
             (add-movie (make-movie :title "Test1" :year 2022))
             (add-movie (make-movie :title "Test3" :year 1984))
             (let ((res (sort-year)))
	       (list (movie-year (aref res 0)) (movie-year (aref res 1)) (movie-year (aref res 2)))))
           '(1966 1984 2022))
    (equal (progn
             (setf *size* 4)
             (setf *db* (make-array *size*  :initial-element nil))
             (sort-year))
           nil)))


(deftest test-in-db-list? ()
  (check
    (equal (progn
	     (setf *db-list* nil)
	     (in-db-list? "test1"))
	   nil)
    (equal (progn
	     (setf *db-list* (list (make-movie :TITLE "test3")
				   (make-movie :TITLE "test2")
				   (make-movie :TITLE "test1")))
	     (let ((res (in-db-list? "test1")))
	       (and (equal (movie-title (elt res 0)) "test3")
		    (equal (movie-title (elt res 1)) "test2")
		    (equal (movie-title (elt res 2)) "test1"))))
	   T)
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1"))
	     (add-movie-list (make-movie :title "test2"))
	     (add-movie-list (make-movie :title "test3"))
	     (in-db-list? "test4"))
	   NIL)))

(deftest test-add-movie-list ()
  (check
    (equal (progn
	     (setf *db-list* nil)
	     (let ((res (add-movie-list (make-movie :title "test1"))))
	       (and (= (length res) 1)
		    (equal (movie-title (elt res 0)) "test1"))))
	   t)
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1"))
	     (add-movie-list (make-movie :title "test2"))
	     (let ((res (add-movie-list (make-movie :title "test3"))))
	       (and (= (length res) 3)
		    (equal (movie-title (elt res 0)) "test3")
		    (equal (movie-title (elt res 1)) "test2")
		    (equal (movie-title (elt res 2)) "test1"))))
	   t)
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1"))
	     (add-movie-list (make-movie :title "test2"))
	     (add-movie-list (make-movie :title "test1")))
	   nil)))

(deftest test-from-year ()
  (check
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1" :year 2022))
	     (add-movie-list (make-movie :title "test2" :year 2022))
	     (from-year 2023))
	   nil)
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1" :year 2022))
	     (add-movie-list (make-movie :title "test2" :year 2022))
	     (add-movie-list (make-movie :title "test3" :year 2023))
	     (let ((res (from-year 2022)))
	       (and (= (length res) 2)
		    (equal (movie-title (elt res 0)) "test1")
		    (equal (movie-title (elt res 1)) "test2"))))
	   t)
    (equal (progn
	     (setf *db-list* nil)
	     (add-movie-list (make-movie :title "test1" :year 2022))
	     (add-movie-list (make-movie :title "test3" :year 2020))
	     (add-movie-list (make-movie :title "test2" :year 2022))
	     (let ((res (from-year 2020)))
	       (and (= (length res) 1)
		    (equal (movie-title (elt res 0)) "test3"))))
	   t)))
	     
	     
(defun test-lab04 ()
  (test-from-year)
  (test-add-movie-list)
  (test-in-db-list?)
  (test-sort-year)
  (test-sort-title))

	     
(test-lab04)
