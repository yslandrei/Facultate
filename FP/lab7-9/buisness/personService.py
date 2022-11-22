from domain.person import person


class personService():
    def __init__(self, pRepo, v):
        self.__pRepo = pRepo
        self.__v = v

    def addPerson(self, id, name, adress):
        Person = person(id, name, adress)
        self.__v.validate(Person)
        self.__pRepo.addPerson(Person)

    def modPerson(self, id, nId, nName, nAdress):
        newPerson = person(nId, nName, nAdress)
        self.__v.validate(newPerson)
        oldPerson = self.__pRepo.getPersonFromId(id)
        self.__pRepo.modPerson(oldPerson, newPerson)

    def srcPerson(self, keyword):
        result = ""
        for i in range(len(self.__pRepo)):
            if str(self.__pRepo.get(i).getId()).find(keyword) != -1:
                result = result + str(self.__pRepo.get(i)) + "\n"
            elif self.__pRepo.get(i).getName().find(keyword) != -1:
                result = result + str(self.__pRepo.get(i)) + "\n"
            elif self.__pRepo.get(i).getAdress().find(keyword) != -1:
                result = result + str(self.__pRepo.get(i)) + "\n"
        if len(result):
            print(result)
        else:
            print("Niciun rezultat gasit!\n")

    def printAll(self):
        for i in range(len(self.__pRepo)):
            if i + 1 != len(self.__pRepo):
                print(f" ├─ {self.__pRepo.get(i)}")
            else:
                print(f" └─ {self.__pRepo.get(i)}")