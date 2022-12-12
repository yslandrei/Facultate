class menu:
    def __init__(self, aService, rService):
        self.aService = aService
        self.rService = rService

    def printMenu(self):
        print('Cauta un apartament dupa numarul de camere                               - sbt [camere]')
        print('Afiseaza pretul de inchiriere al unui apartament pe un anumit nr de luni - prp [nr], [luni]')

    def clearScreen(self):
        print('\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n')

    def run(self):
        self.clearScreen()
        while(True):
            self.printMenu()
            comm = input('Comanda(a = afis, q = quit): ')
            self.clearScreen()

            if comm == 'a':
                print('Apartamente: \n')
                self.aService.printAll()
                print('Inchirieri: \n')
                self.rService.printAll()

            elif comm == 'q':
                self.aService.saveFile()
                return 

            elif comm[:3] == 'sbt':
                try:
                    type = int(comm[4:])
                    printList = self.aService.searchByType(type)
                    for aparmtent in printList:
                        print(aparmtent)
                    print()
                except ValueError as error:
                    print(error)


            elif comm[:3] == 'prp':
                try:
                    comm = comm[4:]
                    nr, months = comm.split(', ')
                    self.rService.addRent(nr, months)
                    self.rService.printLast()
                except ValueError as error:
                    print(error)

            else:
                print('Comanda Invalida!')