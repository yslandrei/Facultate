; nrNodes(l, level, counter) = 
; = 1, daca level = counter
; = 0, daca level != counter
; = nrNodes(l1, level, counter) + nrNodes(l2, level, counter) + ... + nrNodes(ln, level, counter), altfel


(defun nrNodes(l level counter)
  (cond
    ((and (atom l) (equal counter level)) 1)
    ((atom l) 0)
    (t (apply '+ (mapcar #' (lambda (a) (nrNodes a level (+ counter 1))) l)))
  )
)


(print (nrNodes '(A (B (C)) (D) (E (F))) 1 -1))