from validation.validator import validator
from buisness.linkService import linkService
from domain.event import event
from domain.person import person
from domain.link import link
from infrastructure.eventRepository import eventRepository
from infrastructure.linkRepository import linkRepository
from infrastructure.personRepository import personRepository


def testAllLinkFunctionalities():
    testLinkRepository()
    testLinkValidator()
    testLinkService()

def testLinkRepository():
    testLinkRepositoryAdd()
    testLinkRepositoryPopPerson()
    testLinkRepositoryPopEvent()

def testLinkRepositoryAdd():
    lRepo = linkRepository()
    person0 = person(0, "nume", "adresa")
    event0 = event(0, "nume", "data", "timp")
    link0 = link(person0, event0)
    lRepo.addLink(link0)
    assert lRepo.get(0) == link0
    try:
        lRepo.addLink(link0)
        assert False
    except ValueError:
        assert True

def testLinkRepositoryPopPerson():
    lRepo = linkRepository()
    person0 = person(0, "nume", "adresa")
    event0 = event(10, "nume", "data", "timp")
    event1 = event(11, "nume", "data", "timp")
    link0 = link(person0, event0)
    lRepo.addLink(link0)
    link1 = link(person0, event1)
    lRepo.addLink(link1)
    lRepo.popLink(link0)
    assert len(lRepo) == 1

def testLinkRepositoryPopEvent():
    lRepo = linkRepository()
    person0 = person(0, "nume", "adresa")
    person1 = person(1, "nume", "adresa")
    event0 = event(10, "nume", "data", "timp")
    link0 = link(person0, event0)
    lRepo.addLink(link0)
    link1 = link(person1, event0)
    lRepo.addLink(link1)
    lRepo.popLink(link0)
    assert len(lRepo) == 1

def testLinkValidator():
    pass

def testLinkService():
    testLinkServiceAdd()
    testLinkServicePopPersonAndLinksRelated()
    testLinkServicePopEventAndLinksRelated()

def testLinkServiceAdd():
    pRepo = personRepository()
    eRepo = eventRepository()
    lRepo = linkRepository()
    v = validator()
    lService = linkService(pRepo, eRepo, lRepo, v)
    person0 = person(0, "nume", "adresa")
    pRepo.addPerson(person0)
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    lService.addLink(0, 10)
    assert len(lRepo) == 1

def testLinkServicePopPersonAndLinksRelated():
    pRepo = personRepository()
    eRepo = eventRepository()
    lRepo = linkRepository()
    v = validator()
    lService = linkService(pRepo, eRepo, lRepo, v)
    person0 = person(0, "nume", "adresa")
    pRepo.addPerson(person0)
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    lService.popPersonAndLinksRelated(0)
    assert len(lRepo) == 0

def testLinkServicePopEventAndLinksRelated():
    pRepo = personRepository()
    eRepo = eventRepository()
    lRepo = linkRepository()
    v = validator()
    lService = linkService(pRepo, eRepo, lRepo, v)
    person0 = person(0, "nume", "adresa")
    pRepo.addPerson(person0)
    event0 = event(10, "nume", "data", "timp")
    eRepo.addEvent(event0)
    lService.popEventAndLinksRelated(10)
    assert len(lRepo) == 0
    