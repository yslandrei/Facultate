from infrastructure.apartmentRepo import apartmentRepo
from domain.apartment import apartment
from service.apartmentService import apartmentService

def runAllApartmentTests():
    testGetApartmentByNr()
    testSearchByType()

def testGetApartmentByNr():
    aRepo = apartmentRepo()
    Apartment = aRepo.getApartmentByNr(55)
    assert Apartment == apartment(55, 2, 50000, 500)

def testSearchByType():
    aRepo = apartmentRepo()
    aService = apartmentService(aRepo)
    tList = aService.searchByType(2)
    assert len(tList) == 4