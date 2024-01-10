; elimDinNInN(l1...ln, n) = elimDinNInNAux(l1...ln, n, 1)
; elimDinNInNAux(l1...ln, n, pos) =
; = l1 + elimDinNInNAux(l2...ln, n, pos+1), daca n % pos != 0
; = elimDinNInNAux(l2...ln, n, pos+1), altfel


(defun elimDinNInN (l n)
  (elimDinNInNAux l n 1)  
)

(defun elimDinNInNAux (l n pos)
  (cond
    ((null l) nil)
    ((= (mod pos n) 0)  (elimDinNInNAux (cdr l) n (+ pos 1)))
    (t (cons (car l) (elimDinNInNAux (cdr l) n (+ pos 1))))
  )
)

(print (elimDinNInN '(1 2 3 4 5 6) 3))

; vale(l1...ln) = valeAux(l2...ln, l1, 0)
; valeAux(l1...ln, last, dir) =
; valeAux(l2...ln, l1, 0), daca (dir=0 si last>l1)
; valeAux(l2...ln, l1, 1), daca (dir=0 si last<l1)
; valeAux(l2...ln, l1, 1), daca (dir=1 si last<l1)
; false,                   daca (dir=1 si last>l1)
; true, daca l e goala

(defun vale (l)
  (valeAux (cdr l) (car l) 0)
)

(defun valeAux (l last dir)
  (cond
    ((null l) 1)
    ((and (= dir 0) (> last (car l))) (valeAux (cdr l) (car l) 0))
    ((and (= dir 0) (< last (car l))) (valeAux (cdr l) (car l) 1))
    ((and (= dir 1) (< last (car l))) (valeAux (cdr l) (car l) 1))
    ((and (= dir 1) (> last (car l))) 0)
  )
)

(print (vale '(5 4 3 5 6)))

; minNr(l1...ln) = 
; min(l1, minNr(l2...ln)), daca l1 e atom numeric
; minNr(l2...ln), daca l1 e atom dar nu numeric
; min(minNr(l1), minNr(l2...ln)), daca l1 nu e atom

(defun minNr (l)
  (cond
    ((null l) 999999)
    ((numberp (car l)) (min (car l) (minNr (cdr l))))
    ((atom (car l)) (minNr (cdr l)))
    (t (min (minNr (car l)) (minNr (cdr l))))
  )  
)

(print (minNr '(3 4 (2 3 5 (1 0) (4 6 (2))))))

; elimMaxElem(l1...ln) = elimMaxElemAux(l1...ln, maxNr(l1...ln))
;
; maxNr(l1...ln) = 
; max(l1, maxNr(l2...ln))
;
; elimMaxElemAux(l1...ln, nr) = 
; = l1 + elimMaxElemAux(l2...ln, nr), daca l1!=nr
; = elimMaxElemAux(l2...ln, nr), altfel

(defun elimMaxElem (l)
  (elimMaxElemAux l (maxNr l))  
)

(defun maxNr (l) 
  (cond
    ((null l) -9999)
    (t (max (car l) (maxNr (cdr l))))
  )
)

(defun elimMaxElemAux (l nr)
  (cond
    ((null l) nil)
    ((= (car l) nr) (elimMaxElemAux (cdr l) nr))
    (t (cons (car l) (elimMaxElemAux (cdr l) nr)))
  )  
)

(print (elimMaxElem '(1 2 3 3 2 1 3 2 1 1 2)))
