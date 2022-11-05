def createUndoStackElement(transaction, oper, pos):
    return {
        "transaction": transaction,
        "oper": oper,
        "pos": pos
    }

def stackTop(undoStack):
    return len(undoStack) - 1

def updateUndoStack(undoStack):
    undoStack.append(list())

def appendUndoStack(undoStack, undoStackElement):
    undoStack[stackTop(undoStack)].append(undoStackElement)

def undoList(List, undoStack):
    if undoStack == []:
        raise ValueError
    for i in reversed(range(len(undoStack[stackTop(undoStack)]))):
        if undoStack[stackTop(undoStack)][i]["oper"] == "+":
            List.pop(undoStack[stackTop(undoStack)][i]["pos"])  
        elif undoStack[stackTop(undoStack)][i]["oper"] == "-":
            List.insert(undoStack[stackTop(undoStack)][i]["pos"], undoStack[stackTop(undoStack)][i]["transaction"])
        elif undoStack[stackTop(undoStack)][i]["oper"] == "r":
            List[undoStack[stackTop(undoStack)][i]["pos"]] = undoStack[stackTop(undoStack)][i]["transaction"]
    undoStack.pop(stackTop(undoStack))


