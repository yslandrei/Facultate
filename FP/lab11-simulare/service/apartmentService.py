class apartmentService:
    def __init__(self, aRepo):
        self.aRepo = aRepo

    def printAll(self):
        for i in range(len(self.aRepo)):
            print(self.aRepo.get(i))
        print()

    def saveFile(self):
        self.aRepo.saveFile()

    def searchByType(self, type):
        returnList = []
        for i in range(len(self.aRepo)):
            if self.aRepo.get(i).getType() == type:
                returnList.append(self.aRepo.get(i))
        return returnList
