from domain.apartment import apartment


class apartmentRepo:
    def __init__(self):
        self.fileName = 'infrastructure/apartmentData.txt'
        self.aList = []
        self.loadFile()

    def __len__(self):
        return len(self.aList)

    def get(self, i):
        return self.aList[i]

    def getApartmentByNr(self, nr):
        for apartment in self.aList:
            if apartment.getNr() == nr:
                return apartment

    def loadFile(self):
        with open(self.fileName, "r") as f:
            for line in f:
                line = line[2:]
                args = line.strip("\n").split(", ")
                Apartment = apartment(int(args[0]), int(args[1]), int(args[2]), int(args[3]))
                self.aList.append(Apartment)

    def saveFile(self):
        with open(self.fileName, "w") as f:
            for apartment in self.aList:
                line = "Ap " + str(apartment.getNr()) + ", " +  str(apartment.getType()) + ", " + str(apartment.getPrice()) + ", " + str(apartment.getRentPrice()) + "\n"
                f.write(line)
