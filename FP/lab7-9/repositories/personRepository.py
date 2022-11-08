class personRepository:
    def __init__(self):
        self.__pList = []
    
    def get(self, i):
        return self.__pList[i]

    def addPerson(self, person):
        self.__pList.append(person)

    def popPerson(self, id):
        i = 0
        while i < len(self.__pList):
            if self.__pList[i].getId() == id:
                self.__pList.pop(i)
            else:
                i += 1
    
    def modPerson(self, id, newPerson):
        for i in range(len(self.__pList)):
            if self.__pList[i].getId() == id:
                self.__pList[i].set(newPerson)

    def getPersonFromId(self, id):
        for i in range(len(self.__pList)):
             if self.__pList[i].getId() == id:
                return self.__pList[i]

    def searchPerson(self, keyword):
        for i in range(len(self.__pList)):
            if self.__pList[i].search(keyword.lower()):
                print(self.__pList[i])
        print("\n")

    def printAll(self):
        for __person in self.__pList:
            if __person != self.__pList[-1]:
                print(f" ├─ {__person}")
            else:
                print(f" └─ {__person}")




    