from validation.validator import validator
from domain.event import event
from infrastructure.eventRepository import eventRepository
from infrastructure.linkRepository import linkRepository
from buisness.eventService import eventService


def testAllEventFunctionalities():
    testEventRepository()
    testEventValidator()
    testEventService()

def testEventRepository():
    testEventRepositoryAdd()
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
    v = validator()
    v.validate(event0)
    event1 = event(-1, "nume", "data", "timp")
    try:
        v.validate(event1)
        assert False
    except ValueError:
        assert True
    event2 = event("a", "nume", "data", "timp")
    try:
        v.validate(event2)
        assert False
    except ValueError:
        assert True

def testEventService():
    testEventServiceAdd()
    testEventServiceMod()

def testEventServiceAdd():
    eRepo = eventRepository()
    v = validator()
    eService = eventService(eRepo, v)
    eService.addEvent(10, "nume", "data", "timp")
    assert eRepo.get(0) == event(10, "nume", "data", "timp")

def testEventServiceMod():
    eRepo = eventRepository()
    v = validator()
    eService = eventService(eRepo, v)
    eService.addEvent(10, "nume", "data", "timp")
    eService.modEvent(10, 11, "nume1", "data1", "timp1")
    assert eRepo.get(0) == event(11, "nume1", "data1", "timp1")


