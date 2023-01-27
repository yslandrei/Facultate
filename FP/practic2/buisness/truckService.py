import copy
from domain.truck import truck
from infrastructure.truckFileRepository import truckFileRepository
from validation.validators import validateTruck, validateDigit, validateFilters
from datetime import date


class truckService:
    def __init__(self):
        self.tRepo = truckFileRepository('infrastructure/trucks.txt')
        self.nameFilter = "''"
        self.priceFilter = -1
        self.undoStack = []
        self.undoStackTop = -1

    def addTruck(self, id, name, price, model, date):
        '''
        adauga un nou tractor in lista
        '''
        validateTruck(id, name, price, model, date)
        newTruck = truck(int(id), name, int(price), model, date)

        self.tRepo.addTruck(newTruck)
        self.tRepo.saveFile()

        self.undoStack.append(list())
        self.undoStackTop += 1
        self.undoStack[self.undoStackTop].append((newTruck, '+'))
    
    def popTrucks(self, digit):
        '''
        sterge un tractor existent din lista
        '''
        validateDigit(digit)
        self.undoStack.append(list())
        self.undoStackTop += 1
        tList = self.tRepo.getAll()
        counter = 0
        for i in range(len(tList)):
            if digit in str(tList[i - counter].getPrice()):
                self.undoStack[self.undoStackTop].append((tList[i - counter], '-'))

                tList.pop(i - counter)
                counter += 1

        self.tRepo.saveFile()
        return counter

    def setFilters(self, newNameFilter, newPriceFilter):
        '''
        seteaza filtre pentru afisare
        '''
        validateFilters(newNameFilter, newPriceFilter)
        self.nameFilter = newNameFilter
        self.priceFilter = int(newPriceFilter)

    def isExpired(self, tDate):
        '''
        returneaza daca o data este sau nu expirata
        '''
        tDay, tMonth, tYear = tDate.split(':')
        year, month, day = str(date.today()).split('-')

        if tYear < year:
            return True
        elif tYear > year:
            return False
        else:
            if tMonth < month:
                return True
            elif tMonth > month:
                return False
            else:
                if tDay <= day:
                    return True
                elif tDay > day:
                    return False

    def getFilteredList(self):
        '''
        returneaza lista de tractoare dupa filtrul activ
        '''
        tList = self.tRepo.getAll()
        tListFiltered = []
        for i in range(len(tList)):
            if self.nameFilter == "''" or self.nameFilter in tList[i].getName():
                if self.priceFilter == -1 or tList[i].getPrice() < int(self.priceFilter):
                    filteredTruck = copy.deepcopy(tList[i])
                    if self.isExpired(filteredTruck.getDate()):
                        filteredTruck.setName(f'*{tList[i].getName()}')
                    
                    tListFiltered.append(filteredTruck)

        return tListFiltered

    def getFilters(self):
        '''
        returneaza filtrele active
        '''
        return self.nameFilter, self.priceFilter
    
    def undo(self):
        '''
        face un pas de undo
        '''
        removedTrucks = self.undoStack.pop()
        self.undoStackTop -= 1

        for Truck in removedTrucks:
            if Truck[1] == '+':
                self.tRepo.popTruck(Truck[0])
            elif Truck[1] == '-':
                self.tRepo.addTruck(Truck[0])



