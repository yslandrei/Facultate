from buisness.truckService import truckService
from domain.truck import truck
from infrastructure.truckFileRepository import truckFileRepository


def testTruckService():
    testAddTruck()
    testPopTruck()
    testIsExpired()
    testUndo()

def testUndo():
    pass

def testIsExpired():
    tService = truckService()
    
    assert tService.isExpired('17:10:2022') == True

    assert tService.isExpired('20:12:2023') == False

def testSetFilters():
    Truck = truck(0, 'nume', 1234, 'model', 'data')
    tRepo = truckFileRepository('noFile')
    tService = truckService()
    
    
    assert tRepo.tList[0] == Truck

    try:
        tRepo.addTruck(Truck)
        assert False
    except ValueError:
        assert True

def testAddTruck():
    Truck = truck(0, 'nume', 1234, 'model', 'data')
    tRepo = truckFileRepository('noFile')
    tService = truckService()
    
    tRepo.addTruck(Truck)
    assert tRepo.tList[0] == Truck

    try:
        tRepo.addTruck(Truck)
        assert False
    except ValueError:
        assert True

def testPopTruck():
    Truck = truck(0, 'nume', 1234, 'model', 'data')
    tRepo = truckFileRepository('noFile')
    tService = truckService()

    tRepo.addTruck(Truck)
    tRepo.popTruck(Truck)

    assert len(tRepo.tList) == 0

    try:
        tRepo.popTruck(Truck)
        assert False
    except ValueError:
        assert True    
 
