from repositories.eventRepository import eventRepository
from repositories.linkRepository import linkRepository
from repositories.personRepository import personRepository
from service.event import event
from service.person import person
from service.link import link
from validators.validateRepositories import validateEntityIsAlreadyInRepository
from validators.validateIds import validateIdIsAlreadyInRepository, validateId, validateIdInRepository


def testValidateRepo():
    testValidatePIsAlreadyInRepo()
    testValidateEIsAlreadyInRepo()
    testValidateLIsAlreadyInRepo()
    testValidateId()
    testValidateIdInRepository

def testValidatePIsAlreadyInRepo():
    person0 = person(0, "nume0", "adresa0")
    person1 = person(0, "nume1", "adresa0")
    person2 = person(1, "nume0", "adresa2")
    pRepo = personRepository()
    pRepo.addPerson(person0)
    try:
        validateEntityIsAlreadyInRepository(pRepo, person1)
        assert False
    except ValueError as error:
        assert error.args[0] == "ID-ul este deja existent!"
    try:
        validateEntityIsAlreadyInRepository(pRepo, person2)
        assert False
    except ValueError as error:
        assert error.args[0] == "Numele este deja existent!"

def testValidateEIsAlreadyInRepo():
    event0 = event(10, "nume0", "data0", "timp0")
    event1 = event(10, "nume1", "data0", "timp0")
    event2 = event(11, "nume0", "data2", "timp2")
    eRepo = eventRepository()
    eRepo.addEvent(event0)
    try:
        validateEntityIsAlreadyInRepository(eRepo, event1)
        assert False
    except ValueError as error:
        assert error.args[0] == "ID-ul este deja existent!"
    try:
        validateEntityIsAlreadyInRepository(eRepo, event2)
        assert False
    except ValueError as error:
        assert error.args[0] == "Numele este deja existent!"

def testValidateLIsAlreadyInRepo():
    person0 = person(0, "nume0", "adresa0")
    event0 = event(10, "nume0", "data0", "timp0")
    link0 = link(person0, event0)
    lRepo = linkRepository()
    lRepo.addLink(link0)
    try:
        validateEntityIsAlreadyInRepository(lRepo, link0)
        assert False
    except ValueError as error:
        assert error.args[0] == "Persoana este deja inscrisa la acest eveniment!"

def testValidateId():
    id = -1
    try:
        validateId(id)
        assert False
    except ValueError as error:
        assert error.args[0] == "Introduceti un ID pozitiv!"

def testValidateIdInRepository():
    person0 = person(0, "nume0", "adresa0")
    pRepo = personRepository()
    pRepo.addPerson(person0)
    try:
        validateIdInRepository(pRepo, 1)
        assert False
    except ValueError as error:
        assert error.args[0] == "ID-ul nu exista in lista!"
    