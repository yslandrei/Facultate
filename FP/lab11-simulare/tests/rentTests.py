from domain.apartment import apartment
from domain.rent import rent
from infrastructure.rentRepo import rentRepo


def runAllRentTests():
    testAddRent()

def testAddRent():
    rRepo = rentRepo()
    Apartment = apartment(1, 2, 30000, 100)
    Rent = rent(Apartment, 3)
    assert Rent.getPay() == 300
    rRepo.addRent(Rent)
    assert rRepo.get(len(rRepo) - 1) == Rent