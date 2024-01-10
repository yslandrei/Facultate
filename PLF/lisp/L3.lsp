;10.  Definiti o functie care determina numarul nodurilor de pe nivelul kdintr-un arbore n-ar reprezentat sub forma (radacina lista_noduri_subarb1...lista_noduri_subarbn) Ex: arborelele este (a (b (c)) (d) (e (f))) si k=1 => 3 noduri 

; nrNodes(l, level, counter) = 
; = 1, if level = counter
; = 0, if level != counter
; = nrNodes(l1, level, counter) + nrNodes(l2, level, counter) + ... + nrNodes(ln, level, counter), otherwise


(defun nrNodes(l level counter)
  (cond
    ((and (atom l) (equal counter level)) 1)
    ((atom l) 0)
    (t (apply '+ (mapcar #' (lambda (a) (nrNodes a level (+ counter 1))) l)))
  )
)


(defun main(l level)
  (nrNodes l level -1)
)