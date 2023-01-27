from domain.truck import truck


class truckFileRepository:
    def __init__(self, filename):
        self.fileName = filename
        self.tList = []
        self.loadFile()

    def getAll(self):
        '''
        returneaza tot repository-ul de tractoare
        '''
        return self.tList

    def loadFile(self):
        '''
        da load la tractoare din fisier in repository
        '''
        if self.fileName == 'noFile':
            return
        with open(self.fileName, "r") as f:
            for line in f:
                args = line.strip("\n").split(", ")
                Truck = truck(int(args[0]), args[1], int(args[2]), args[3], args[4])
                self.tList.append(Truck)

    def saveFile(self):
        '''
        salveaza toate tractoarele in fisier din repository
        '''
        if self.fileName == 'noFile':
            return
        with open(self.fileName, "w") as f:
            for Truck in self.tList:
                line = str(Truck.getId()) + ", " + Truck.getName() + ", " + str(Truck.getPrice()) + ", " + Truck.getModel() + ', ' + Truck.getDate() + "\n"
                f.write(line)

    def addTruck(self, newTruck):
        '''
        adauga in repository un nou tractor
        '''
        for truck in self.tList:
            if truck.getId() == newTruck.getId():
                raise ValueError('Id deja existent in lista de tractoare')
        self.tList.append(newTruck)

    def popTruck(self, oldTruck):
        '''
        sterge din repository un tractor vechi
        '''
        for i  in range(len(self.tList)):
            if self.tList[i] == oldTruck:
                self.tList.pop(i)
                return
        raise ValueError('Nu exista niciun tractor cu aceste specificatii!')
        
