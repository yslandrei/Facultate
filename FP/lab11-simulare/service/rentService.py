from domain.rent import rent


class rentService:
    def __init__(self, aRepo, rRepo):
        self.aRepo = aRepo
        self.rRepo = rRepo

    def addRent(self, nr, months):
        Apartment = self.aRepo.getApartmentByNr(int(nr))
        Rent = rent(Apartment, int(months))
        self.rRepo.addRent(Rent)

    def printAll(self):
        for i in range(len(self.rRepo)):
            print(self.rRepo.get(i))
        print()

    def printLast(self):
        print(self.rRepo.get(len(self.rRepo) - 1))
        print()
