from complexNumb import complexNumb


class undo:
    """
    Clasa pentru lista undo
    numar = a + bi
    a, b - partea reala/imaginara a numarului adaugat/scos
    oper - operatia efectuata (+ = add, - = pop)
    pos - pozitia operatiei efectuata
    """
    def __init__(self, a, b, oper, pos):
        self.a = a
        self.b = b
        self.oper = oper
        self.pos = pos
        
def undoList(List, undoStack):
    """
    Reface ultima operație
    undoStack retine pe fiecare pozitie operatiile de adaugare/eliminare efectuate de 
    ultima comanda, si le oglindeste astfel incat Lista revine cu un pas in spate
    """
    if(undoStack == [list()]):
        raise ValueError
    undoStack.pop(len(undoStack) - 1)
    for i in reversed(range(len(undoStack[len(undoStack) - 1]))):
        if undoStack[len(undoStack) - 1][i].oper == "+":
            List.pop(undoStack[len(undoStack) - 1][i].pos)
        elif undoStack[len(undoStack) - 1][i].oper == "-":
            List.insert(undoStack[len(undoStack) - 1][i].pos, complexNumb(undoStack[len(undoStack) - 1][i].a, undoStack[len(undoStack) - 1][i].b))
    undoStack.pop(len(undoStack) - 1)
    undoStack.append(list())