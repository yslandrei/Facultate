class ui():
    def __init__(self, pService, eService, lService):
        self.__pService = pService
        self.__eService = eService
        self.__lService = lService

    def printMenu(self):
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

    def clearScreen(self):
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

    def printAllData(self):
        print("📁 Persoane:")
        self.__pService.printAll()
        print("\n📁 Evenimente:")
        self.__eService.printAll()
        print("\n📁 Participari:")
        self.__lService.printAll()
        print("\n")

    def preloadData(self):
        self.__pService.addPerson(0, "Andrei Diaconescu", "Valcea")
        self.__pService.addPerson(1, "Teodor Domnica", "Prahova")
        self.__pService.addPerson(2, "Andrei Ivancu", "Valcea")
        self.__pService.addPerson(3, "Rares Bozga", "Satu Mare")
        self.__eService.addEvent(10, "Untold", "04.08.2023", "4 zile")
        self.__eService.addEvent(11, "Electric Castle", "13.07.2023", "3 zile")
        self.__eService.addEvent(12, "Hustle", "01.12.2022", "2 zile")
        self.__eService.addEvent(13, "Neversea", "15.08.2023", "3 zile")
        self.__eService.addEvent(14, "Saga", "28.08.2023", "2 zile")
        self.__lService.addLink(0, 10)
        self.__lService.addLink(0, 11)
        self.__lService.addLink(0, 12)
        self.__lService.addLink(1, 11)
        self.__lService.addLink(1, 10)
        self.__lService.addLink(1, 13)
        self.__lService.addLink(2, 10)
        self.__lService.addLink(2, 11)
        self.__lService.addLink(3, 10)
        self.__lService.addLink(3, 14)   
        
    def run(self):
        self.preloadData()
        self.clearScreen()
        while(True):
            self.printMenu()
            command = input("\nIntroduceti Comanda(a = afisare date, q = quit):")
            self.clearScreen()
            if command == "q":
                return
            elif command == "a":
                self.printAllData()
            elif command[:4] == "addP":
                try:
                    id, name, adress = command[5:].split(", ")
                    self.__pService.addPerson(int(id), name, adress)
                except ValueError as error:
                    print(error)
            elif command[:4] == "popP":
                try:
                    id = command[5:]
                    self.__pService.popPerson(int(id))
                except ValueError as error:
                    print(error)
            elif command[:4] == "modP":
                try:
                    id, nId, nName, nAdress = command[5:].split(", ")
                    self.__pService.modPerson(int(id), int(nId), nName, nAdress)
                except ValueError as error:
                    print(error)
            elif command[:4] == "srcP":
                try:
                    keyword = command[5:]
                    self.__pService.srcPerson(keyword)
                except ValueError as error:
                    print(error)
            elif command[:4] == "addE":
                try:
                    id, name, date, time = command[5:].split(", ")
                    self.__eService.addEvent(int(id), name, date, time)
                except ValueError as error:
                    print(error)
            elif command[:4] == "popE":
                try:
                    id = command[5:]
                    self.__eService.popEvent(int(id))
                except ValueError as error:
                    print(error)
            elif command[:4] == "modE":
                try:
                    id, nId, nName, nDate, nTime = command[5:].split(", ")
                    self.__eService.modEvent(int(id), int(nId), nName, nDate, nTime)
                except ValueError as error:
                    print(error)
            elif command[:4] == "srcE":
                try:
                    keyword = command[5:]
                    self.__eService.srcEvent(keyword)
                except ValueError as error:
                    print(error)
            elif command[:4] == "link":
                try:
                    pId, eId = command[5:].split(", ")
                    self.__lService.addLink(int(pId), int(eId))
                except ValueError as error:
                    print(error)
            elif command[:4] == "ppes":
                try:
                    id = command[5:]
                    print(self.__lService.getPersonsEvents(int(id)))
                except ValueError as error:
                    print(error)
            elif command[:4] == "pmep":
                try:
                    print(self.__lService.getMostEventsAPersonParticipates())
                except ValueError as error:
                    print(error)
            elif command[:4] == "pmpe":
                try:
                    print(self.__lService.getMostParticipatedEvents())
                except ValueError as error:
                    print(error)  
            else:
                print("Comanda Invalida!")