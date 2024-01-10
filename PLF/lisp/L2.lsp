;11. Se da un arbore de tipul (2). Sa se afiseze nivelul (si lista corespunza-toarea nodurilor) avand numar maxim de noduri. Nivelul rad. se considera 0


; (car l) - the first element of the list is the root of the tree
; (cadr l) - the second element of the list, at superficial level, is the left subtree
; (caddr l) - the third element of the list, at the superficial level, is the right subtree


; myAppend(l1l2...ln, p1p2...pm) = 
; = p1p2...pm, if n = 0
; = {l1} U myAppend(l2...ln, p1p2...pm), otherwise


(defun myAppend (l p)
  (cond
    ((null l) p)
    (t (cons (car l) (myAppend (cdr l) p)))
  )
)

; myMax(a,b) = 
; = a, if a > b
; = b, otherwise

(defun myMax(a b)
  (cond
    ((> a b) a)
    (t b)
  )
)

; findLevel(l1l2l3, elem, counter) = 
; = counter, if l1l2l3 is empty
; = myMax(findLevel(l2, elem, counter + 1),findLevel(l3, elem, counter + 1)), otherwise

(defun findMaxLevel(l counter)
  (cond
    ((null l) counter)
    (t (myMax (findMaxLevel (cadr l) (+ 1 counter)) (findMaxLevel (caddr l) (+ 1 counter))))
  )
)


; nodesFromLevel(l1l2l3, level, counter)
; = nil, if l1l2l3 is empty
; = l1 , if counter = level
; = myAppend((list (nodesFromLevel(l2, level, counter + 1))) (list (nodesFromLevel(l3, level, counter + 1)))), otherwise

(defun nodesFromLevel(l level counter)
  (cond
    ((null l) nil)
    ((equal counter level) (list (car l)))
    (t (myAppend (nodesFromLevel (cadr l) level (+ 1 counter)) (nodesFromLevel (caddr l) level (+ 1 counter))))
  )
)


(defun main(l)
  (nodesFromLevel l (findMaxLevel l -1) 0)
)