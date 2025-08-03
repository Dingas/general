(defun filter-seq (s a)
    (setq result)
    (loop for x across s
        (loop for y across a
            if (equal (char s x) (char a y) concatenate 'string result (char s x))
        )
    )
    result
)