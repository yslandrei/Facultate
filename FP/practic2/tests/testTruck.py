from domain.truck import truck


def testTruck():
    testGettersTruck()
    testSettersTruck()

def testGettersTruck():
    Truck = truck(0, 'nume', 1234, 'model', 'data')

    assert Truck.getId() == 0

    assert Truck.getName() == 'nume'

    assert Truck.getPrice() == 1234

    assert Truck.getModel() == 'model'

    assert Truck.getDate() == 'data'

def testSettersTruck():
    Truck = truck(0, 'nume', 1234, 'model', 'data')
    Truck.setName('altNume')

    assert Truck.name == 'altNume'

