(defstruct movie
  title  director year type)

(defparameter *size* 3)

(defvar *db*)

(setf *db* (make-array *size*  :initial-element nil))

(defvar *db-list*)

(setf *db-list*  nil)  

(defun quicksort (vec comp)
  (when (> (length vec) 1)
    (let ((pivot-i 0)
          (pivot (aref vec (1- (length vec)))))
      (dotimes (i (1- (length vec)))
        (when (funcall comp (aref vec i) pivot)
          (rotatef (aref vec i)
                   (aref vec pivot-i))
          (incf pivot-i)))
      (rotatef (aref vec (1- (length vec)))
               (aref vec pivot-i))
      (quicksort (rtl:slice vec 0 pivot-i) comp)
      (quicksort (rtl:slice vec (1+ pivot-i)) comp)))
  vec)

(defun add-movie (m)
  "Adds a movie to the DB and returns true"
  (dotimes (i *size*)
    (when (null (aref *db* i))
      (setf (aref *db* i) m)
      (return *db*))))

(defun add-movie-list (m)
    
  "Adds a movie to the end of *db-list* and returns the list"
  (setf *db-list* (append *db-list* (list m))))
  
  
  
  
(defun checker (m)
   ; (dotimes (i *size*)
   ; (when (and (typep (aref *db* i) 'movie))
   ;            (equalp (aref *db* i) m)
   ;            (return T))
);)


(defun year-checker (m)
    ;(dotimes (i *size*)
   ; (when (and (typep (aref *db* i) 'movie))
   ;            (equal (movie-year (aref *db* i)) movie-year m)
    ;           (return T))
);)

(defun title-checker (m)
    ;(dotimes (i *size*)
    ;(when (and (typep (aref *db* i) 'movie))
               ;(equal (movie-title (aref *db* i)) movie-title m))
);)





(defun sort-title ()
    ;(if (not(null title-checker (*db*)))
        
        
        
    
    ;)
    
)

(defun sort-year ()
    ;(if (not(null year-checker (*db*)))
        
        
        
    
    ;)
    
)


(defun in-db-list? (m nm)
    
    
)


(defun from-year (year)
    
    
    
)

  
(defun add-movie-list-helper (m)
    
    
)



