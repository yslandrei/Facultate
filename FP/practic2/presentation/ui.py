from buisness.truckService import truckService


class ui:
    def __init__(self):
        self.tService = truckService()

    def clearScreen(self):
        '''
        curata ecranul
        '''
        print('\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n')

    def printMenu(self):
        '''
        afiseaza meniul       
        '''
        print('• Adauga tractor                                     - add [id], [nume], [pret], [model], [data]')
        print('• Sterge tractoare ce au in pret cifra data          - pop [digit]')
        print('• Seteaza filtre                                     - set [filtruNume], [filtruPret]')
        print('• Undo ultima operatie(adaugare/stergere)            - und')

    def printFilteredList(self):
        '''
        afiseaza lista filtrata
        '''
        tListFiltered = self.tService.getFilteredList()

        for truck in tListFiltered:
            print(f'{truck.getName()}(id: {str(truck.getId())}, pret: {str(truck.getPrice())}, model: {truck.getModel()}, data: {truck.getDate()})')
        print()

    def runMenu(self):
        '''
        porneste meniul
        '''
        self.clearScreen()
        while True:
            self.printFilteredList()
            self.printMenu()
            nameFilter, priceFilter = self.tService.getFilters()
            com = input(f'Introduceti comanda(Filtre active: Nume({nameFilter}), Pret({priceFilter})): ')
            self.clearScreen()

            if com[:3] == 'add':
                try:
                    com = com[4:]
                    id, name, price, model, date = com.strip('\n').split(', ')
                    self.tService.addTruck(id, name, price, model, date)
                except ValueError as err:
                    print(err, end = '\n\n')

            elif com[:3] == 'pop':
                try:
                    com = com[4:]
                    digit = com.strip('\n')
                    counter = self.tService.popTrucks(digit)
                    print(f'Au fost sterse {counter} tractoare')
                except ValueError as err:
                    print(err, end = '\n\n')

            elif com[:3] == 'set':
                try:
                    com = com[4:]
                    newNameFilter, newPriceFilter = com.strip('\n').split(', ')
                    self.tService.setFilters(newNameFilter, newPriceFilter)
                except ValueError as err:
                    print(err, end = '\n\n')

            elif com[:3] == 'und':
                try:
                    self.tService.undo()
                except ValueError as err:
                    print(err, end = '\n\n')

            elif com == 'q':
                return
            
            else:
                print('Comanda nu exista')
