from repositories.eventRepository import eventRepository
from repositories.linkRepository import linkRepository
from repositories.personRepository import personRepository
from service.event import event
from service.person import person
from service.link import link
from validators.validateRepositories import validateEntityIsAlreadyInRepository
from validators.validateIds import validateIdIsAlreadyInRepository, validateId, validateIdInRepository


class menu():
    def __init__(self):
        self.__pRepo = personRepository()
        self.__eRepo = eventRepository()
        self.__lRepo = linkRepository()

    def __printMenu(self):
        print("• Adauga persoana in lista                                          - addP [id], [nume], [adresa]")
        print("• Sterge persoana din lista                                         - popP [id]")
        print("• Modifica persoana din lista                                       - modP [id], [nId], [nNume], [nAdresa]")
        print("• Cauta persoana in lista                                           - srcP [keyword]")
        print("• Adauga eveniment in lista                                         - addE [id], [nume], [data], [timp]")
        print("• Sterge eveniment din lista                                        - popE [id]")
        print("• Modifica eveniment din lista                                      - modE [id], [nId], [nNume], [nData], [nTimp]")
        print("• Cauta eveniment in lista                                          - srcE [keyword]")
        print("• Inscrie persoana la eveniment                                     - link [pId], [eId]")
        print("• Afiseaza evenimentele la care participa o persoana ordonate dupa  - ppes [pId]")
        print("  nume si data")
        print("• Afiseaza persoanele participante la cele mai multe evenimente     - pmep")
        print("• Afiseaza primele 20% din evenimente cu cei mai multi participanti - pmpe")

    def __clearScreen(self):
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

    def __printAllRepos(self):
        print("📁 Persoane:")
        self.__pRepo.printAll()
        print("\n📁 Evenimente:")
        self.__eRepo.printAll()
        print("\n📁 Participari:")
        self.__lRepo.printAll()
        print("\n")

    def printError(self, error):
        if error[-1] == '!':
            print(error)
        else:
            print("Sintaxa Invalida!")
        print("\n")

    def __loadRepos(self):
        andrei = person(0, "Andrei Diaconescu", "Valcea")
        teodor = person(1, "Teodor Domnica", "Prahova")
        ivancu = person(2, "Andrei Ivancu", "Valcea")
        rares = person(3, "Rares Bozga", "Satu Mare")
        self.__pRepo.addPerson(andrei)
        self.__pRepo.addPerson(teodor)
        self.__pRepo.addPerson(ivancu)
        self.__pRepo.addPerson(rares)
        untold = event(10, "Untold", "04.08.2023", "4 zile")
        electric = event(11, "Electric Castle", "13.07.2023", "3 zile")
        hustle = event(12, "Hustle", "01.12.2022", "2 zile")
        neversea = event(13, "Neversea", "15.08.2023", "3 zile")
        saga = event(14, "Saga", "28.08.2023", "2 zile")
        self.__eRepo.addEvent(untold)
        self.__eRepo.addEvent(electric)
        self.__eRepo.addEvent(hustle)
        self.__eRepo.addEvent(neversea)
        self.__eRepo.addEvent(saga)
        link0 = link(andrei, untold)
        link1 = link(andrei, electric)
        link2 = link(andrei, hustle)
        link3 = link(teodor, electric)
        link4 = link(teodor, untold)
        link5 = link(teodor, neversea)
        link6 = link(ivancu, untold)
        link7 = link(ivancu, electric)
        link8 = link(rares, untold)
        link9 = link(rares, saga)
        self.__lRepo.addLink(link0)
        self.__lRepo.addLink(link1)
        self.__lRepo.addLink(link2)
        self.__lRepo.addLink(link3)
        self.__lRepo.addLink(link4)
        self.__lRepo.addLink(link5)
        self.__lRepo.addLink(link6)
        self.__lRepo.addLink(link7)
        self.__lRepo.addLink(link8)
        self.__lRepo.addLink(link9)

    def runMenu(self):
        self.__loadRepos()
        self.__clearScreen()
        while(True):
            self.__printMenu()
            command = input("\nIntroduceti Comanda(a = afis liste, q = quit):")
            self.__clearScreen()
            if command == "q":
                return
            elif command == "a":
                self.__printAllRepos()
            elif command[:4] == "addP":
                try:
                    id, name, adress = command[5:].split(", ")
                    validateId(int(id))
                    validateIdIsAlreadyInRepository(self.__pRepo, int(id), -1)
                    validateIdIsAlreadyInRepository(self.__eRepo, int(id), -1)
                    newPerson = person(int(id), name, adress)
                    validateEntityIsAlreadyInRepository(self.__pRepo, newPerson)
                    self.__pRepo.addPerson(newPerson)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "popP":
                try:
                    id = command[5:]
                    validateId(int(id))
                    validateIdInRepository(self.__pRepo, int(id))
                    self.__pRepo.popPerson(int(id))
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "modP":
                try:
                    id, nId, nName, nAdress = command[5:].split(", ")
                    validateId(int(id))
                    validateId(int(nId))
                    validateIdInRepository(self.__pRepo, int(id))
                    validateIdIsAlreadyInRepository(self.__pRepo, int(nId), int(id))
                    validateIdIsAlreadyInRepository(self.__eRepo, int(nId), int(id))
                    newPerson = person(int(nId), nName, nAdress)
                    self.__pRepo.modPerson(int(id), newPerson)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "srcP":
                try:
                    keyword = command[5:]
                    self.__pRepo.searchPerson(keyword)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "addE":
                try:
                    id, name, date, time = command[5:].split(", ")
                    validateId(int(id))
                    validateIdIsAlreadyInRepository(self.__eRepo, int(id), -1)
                    validateIdIsAlreadyInRepository(self.__pRepo, int(id), -1)
                    newEvent = event(int(id), name, date, time)
                    validateEntityIsAlreadyInRepository(self.__eRepo, newEvent)
                    self.__eRepo.addEvent(newEvent)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "popE":
                try:
                    id = command[5:]
                    validateId(int(id))
                    validateIdInRepository(self.__eRepo, int(id))
                    self.__eRepo.popEvent(int(id))
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "modE":
                try:
                    id, nId, nName, nDate, nTime = command[5:].split(", ")
                    validateId(int(id))
                    validateId(int(nId))
                    validateIdInRepository(self.__eRepo, int(id))
                    validateIdIsAlreadyInRepository(self.__eRepo, int(nId), int(id))
                    validateIdIsAlreadyInRepository(self.__pRepo, int(nId), int(id))
                    newEvent = event(int(nId), nName, nDate, nTime)
                    self.__eRepo.modEvent(int(id), newEvent)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "srcE":
                try:
                    keyword = command[5:]
                    self.__eRepo.searchEvent(keyword)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "link":
                try:
                    pId, eId = command[5:].split(", ")
                    validateId(int(pId))
                    validateId(int(eId))
                    validateIdInRepository(self.__pRepo, int(pId))
                    validateIdInRepository(self.__eRepo, int(eId))
                    lPerson = self.__pRepo.getPersonFromId(int(pId))
                    lEvent = self.__eRepo.getEventFromId(int(eId))
                    newLink = link(lPerson, lEvent)
                    validateEntityIsAlreadyInRepository(self.__lRepo, newLink)
                    self.__lRepo.addLink(newLink)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "ppes":
                try:
                    id = command[5:]
                    validateIdInRepository(self.__pRepo, int(id))
                    lPerson = self.__pRepo.getPersonFromId(int(id))
                    self.__lRepo.printPersonsEvents(lPerson)
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "pmep":
                try:
                    self.__lRepo.printMostEventsAPersonParticipates()
                except ValueError as error:
                    self.printError(error.args[0])
            elif command[:4] == "pmpe":
                try:
                    self.__lRepo.printMostParticipatedEvents()
                except ValueError as error:
                    self.printError(error.args[0])   
            else:
                print("Comanda Invalida!")