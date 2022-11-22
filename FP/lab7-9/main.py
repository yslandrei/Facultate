from validation.validator import validator
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
    v = validator()
    pRepo = personRepository()
    eRepo = eventRepository()
    lRepo = linkRepository()
    pService = personService(pRepo, v)
    eService = eventService(eRepo, v)
    lService = linkService(pRepo, eRepo, lRepo, v)
    Ui = ui(pService, eService, lService)
    Ui.run()

if __name__ == "__main__":
    main()