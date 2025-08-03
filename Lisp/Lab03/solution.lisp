(defstruct movie
  title  director year type)

(defparameter *size* 3) 

(defvar *db*)
(defvar *dbTEMP*)

(setf *db* (make-array *size*  :initial-element nil))

(defun add-movie (m)
  "Adds a movie to *db* and returns *db*"
  (if (not(in-db? (movie-title m)))
  
  (dotimes (i *size*)
    (when (null (aref *db* i))
      (setf (aref *db* i) m)
      (return *db*)))))

(defun in-db? (title)
  "Returns *db* if movie title is in the database; otherwise returns NIL"
  (dotimes (i *size*)
    (when (and (typep (aref *db* i) 'movie)
               (equal (movie-title (aref *db* i)) title))
      (return *db*))))
      
(defun replace-movie (m nm)
    (if (not(in-db? (movie-title nm)))
      (dotimes (i *size*)
        (when (and (typep (aref *db* i) 'movie)
                   (equal (movie-title (aref *db* i)) (movie-title m)))
                   (setf (aref *db* i) m)
                   (return *db*)))))

(defun check-match (title)

    (dotimes (i *size*)
    (when (and (typep (aref *db* i) 'movie)
               (equal (movie-title (aref *db* i)) title))
      (return T))))



(defun num-movies ()
    (setf movie-count 0)
    (dotimes (i *size*)
        (unless (null (aref *db* i))
            (incf movie-count)))
    movie-count)


    
            

      
      
(defun delete-movie (title)
    (if (check-match (title))
        (progn 
    
    )
        

    
      )



