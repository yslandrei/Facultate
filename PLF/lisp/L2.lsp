;11. Se da un arbore de tipul (2). Sa se afiseze nivelul (si lista corespunza-toarea nodurilor) avand numar maxim de noduri. Nivelul rad. se considera 0

; myAppend(l1...ln, p1...pm) = 
; = p1...pm, daca n = 0
; = l1 + myAppend(l2...ln, p1...pm), altfel


(defun myAppend (l p)
  (cond
    ((null l) p)
    (t (cons (car l) (myAppend (cdr l) p)))
  )
)

; myMax(a,b) = 
; = a, daca a > b
; = b, altfel

(defun myMax(a b)
  (cond
    ((> a b) a)
    (t b)
  )
)


; findNodesOfLevel(l1...ln, level, currLevel)
; = 0, daca l1...ln e goala 
; = 1, daca currLevel = level
; = findNodesOfLevel(l2...ln, level, currLevel + 1) + findNodesOfLevel(l3...ln, level, currLevel + 1)


(defun findNodesOfLevel(l level currLevel)
  (cond 
    ((null l) 0)
    ((= currLevel level) 1)
    (t (+ (findNodesOfLevel (cadr l) level (+ currLevel 1)) (findNodesOfLevel (caddr l) level (+ currLevel 1))))
  )  
)


; findMaxLevel(l1...ln, currLevel, maxLevel, chosenLevel) =
; = maxLevel, daca findNodesOfLevel(l1...ln, currLevel, 0) = 0
; = findMaxLevel(l1...ln, currLevel + 1, myMax(maxLevel, findNodesOfLevel(l1...ln, currLevel, 0)) currLevel), daca maxLevel < findNodesOfLevel(l1...ln, currLevel, 0)
; = findMaxLevel(l1...ln, currLevel + 1, myMax(maxLevel, findNodesOfLevel(l1...ln, currLevel, 0)) chosenLevel), altfel


(defun findMaxLevel(l currLevel maxLevel chosenLevel)
  (cond
    ((= (findNodesOfLevel l currLevel 0) 0) chosenLevel)
    (t 
     (findMaxLevel 
        l 
        (+ currLevel 1) 
        (myMax maxLevel (findNodesOfLevel l currLevel 0))
        (if (< maxLevel (findNodesOfLevel l currLevel 0))
          currLevel
          chosenLevel
        )
      )
    )
  )  
)

; nodesFromLevel(l1...ln, level, counter)
; = nil, daca l1...ln e goala
; = l1 , daca counter = level
; = myAppend((list (nodesFromLevel(l2, level, counter + 1))) (list (nodesFromLevel(l3, level, counter + 1)))), altfel

(defun nodesFromLevel(l level counter)
  (cond
    ((atom l) nil)
    ((equal counter level) (list (car l)))
    (t (myAppend (nodesFromLevel (cadr l) level (+ 1 counter)) (nodesFromLevel (caddr l) level (+ 1 counter))))
  )
)

(setq list '(A (B (F)) (C (D) (E))))
(print (findMaxLevel list 0 0 0))
(print (nodesFromLevel list (findMaxLevel list 0 0 0) 0))

