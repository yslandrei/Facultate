from presentation.ui import ui
from tests.testTruck import testTruck
from tests.testTruckFileRepository import testTruckFileRepository
from tests.testTruckService import testTruckService
from tests.testValidators import testValidators


def main():
    testTruck()
    testValidators()
    testTruckFileRepository()
    testTruckService()

    UI = ui()
    UI.runMenu()

if __name__ == '__main__':
    main()