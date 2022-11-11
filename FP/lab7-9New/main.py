from buisness.eventService import eventService
from buisness.linkService import linkService
from buisness.personService import personService
from infrastructure.eventRepository import eventRepository
from infrastructure.linkRepository import linkRepository
from infrastructure.personRepository import personRepository
from presentation.ui import ui
from tests.testAllFunctionalities import runAllTests


def main():
    runAllTests()
    pRepo = personRepository()
    eRepo = eventRepository()
    lRepo = linkRepository()
    pService = personService(pRepo, lRepo)
    eService = eventService(eRepo, lRepo)
    lService = linkService(pRepo, eRepo, lRepo)
    Ui = ui(pService, eService, lService)
    Ui.run()

if __name__ == "__main__":
    main()