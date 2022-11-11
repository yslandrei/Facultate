from domain.event import event
from infrastructure.eventRepository import eventRepository
from infrastructure.linkRepository import linkRepository
from validation.eventValidator import validateEvent
from buisness.eventService import eventService


def testAllEventFunctionalities():
    testEventRepository()
    testEventValidator()
    testEventService()

def testEventRepository():
    testEventRepositoryAdd()
    testEventRepositoryPop()
    testEventRepositoryMod()
    testEventRepositoryGetEventFromId()

def testEventRepositoryAdd():
    eRepo = eventRepository()
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    assert eRepo.get(0) == event0
    try:
        eRepo.addEvent(event0)
        assert False
    except ValueError:
        assert True

def testEventRepositoryPop():
    eRepo = eventRepository()
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    eRepo.popEvent(event0)
    assert len(eRepo) == 0

def testEventRepositoryMod():
    eRepo = eventRepository()
    event0 = event(10, "nume", "data", "timp")
    event1 = event(11, "nume1", "data1", "timp1")
    eRepo.addEvent(event0)
    eRepo.modEvent(event0, event1)
    assert eRepo.get(0) == event1
    event2 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event2)
    event3 = event(10, "nume2", "data2", "timp2")
    try:
        eRepo.modEvent(event1, event3)
        assert False
    except ValueError:
        assert True

def testEventRepositoryGetEventFromId():
    eRepo = eventRepository()
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    assert eRepo.getEventFromId(10) == event0
    try:
        eRepo.getEventFromId(11)
        assert False
    except ValueError:
        assert True


def testEventValidator():
    event0 = event(10, "nume", "data", "timp")
    validateEvent(event0)
    event1 = event(-1, "nume", "data", "timp")
    try:
        validateEvent(event1)
        assert False
    except ValueError:
        assert True
    event2 = event("a", "nume", "data", "timp")
    try:
        validateEvent(event2)
        assert False
    except ValueError:
        assert True

def testEventService():
    testEventServiceAdd()
    testEventServicePop()
    testEventServiceMod()

def testEventServiceAdd():
    eRepo = eventRepository()
    lRepo = linkRepository()
    eService = eventService(eRepo, lRepo)
    eService.addEvent(10, "nume", "data", "timp")
    assert eRepo.get(0) == event(10, "nume", "data", "timp")

def testEventServicePop():
    eRepo = eventRepository()
    lRepo = linkRepository()
    eService = eventService(eRepo, lRepo)
    eService.addEvent(10, "nume", "data", "timp")
    eService.popEvent(10)
    assert len(eRepo) == 0

def testEventServiceMod():
    eRepo = eventRepository()
    lRepo = linkRepository()
    eService = eventService(eRepo, lRepo)
    eService.addEvent(10, "nume", "data", "timp")
    eService.modEvent(10, 11, "nume1", "data1", "timp1")
    assert eRepo.get(0) == event(11, "nume1", "data1", "timp1")


