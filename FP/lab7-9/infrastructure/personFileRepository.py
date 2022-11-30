from domain.person import person


class personFileRepository:
    def __init__(self):
        self.__fileName = "lab7-9\infrastructure\personData.txt"
        self.__pList = []
        self.loadFile()

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

    def loadFile(self):
        with open(self.__fileName, "r") as f:
            for line in f:
                args = line.strip("\n").split(", ")
                Person = person(int(args[0]), args[1], args[2])
                self.__pList.append(Person)

    def saveFile(self):
        with open(self.__fileName, "w") as f:
            for person in self.__pList:
                line = str(person.getId()) + ", " + person.getName() + ", " + person.getAdress() + "\n"
                f.write(line)
