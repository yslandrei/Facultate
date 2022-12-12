from infrastructure.apartmentRepo import apartmentRepo
from infrastructure.rentRepo import rentRepo
from service.apartmentService import apartmentService
from service.rentService import rentService
from presentation.menu import menu
from tests.allTests import runAllTests


def main():
    runAllTests()
    aRepo = apartmentRepo()
    rRepo = rentRepo()
    aService = apartmentService(aRepo) 
    rService = rentService(aRepo, rRepo)
    ui = menu(aService, rService)
    ui.run()


if __name__ == '__main__':
    main()