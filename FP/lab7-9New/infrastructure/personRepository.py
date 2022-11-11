class personRepository:
    def __init__(self):
        self.__pList = []
    
    def get(self, i):
        return self.__pList[i]

    def __len__(self):
        return len(self.__pList)

    def addPerson(self, person):
        for i in range(len(self.__pList)):
            if self.__pList[i].getId() == person.getId():
                raise ValueError("ID deja existent!\n")
        self.__pList.append(person)

    def popPerson(self, Person):
        for i in range(len(self.__pList)):
            if self.__pList[i].getId() == Person.getId():
                self.__pList.pop(i)
                break
    
    def modPerson(self, oldPerson, newPerson):
        for i in range(len(self.__pList)):
            if self.__pList[i].getId() == newPerson.getId() and oldPerson.getId() != newPerson.getId():
                raise ValueError("Noul ID deja existent!\n")
        for i in range(len(self.__pList)):
            if self.__pList[i].getId() == oldPerson.getId():
                self.__pList[i].set(newPerson)
                break

    def getPersonFromId(self, id):
        for i in range(len(self.__pList)):
             if self.__pList[i].getId() == id:
                return self.__pList[i]
        raise ValueError("ID inexistent!\n")
