from domain.truck import truck
from infrastructure.truckFileRepository import truckFileRepository


def testTruckFileRepository():
    testAddTruck()
    testPopTruck()

def testAddTruck():
    Truck = truck(0, 'nume', 1234, 'model', 'data')
    tRepo = truckFileRepository('noFile')
    
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

    tRepo.addTruck(Truck)
    tRepo.popTruck(Truck)

    assert len(tRepo.tList) == 0

    try:
        tRepo.popTruck(Truck)
        assert False
    except ValueError:
        assert True    
