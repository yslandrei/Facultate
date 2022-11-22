from validation. validator import validator
from domain.person import person
from infrastructure.personRepository import personRepository
from infrastructure.linkRepository import linkRepository
from buisness.personService import personService


def testAllPersonFunctionalities():
    testPersonRepository()
    testPersonValidator()
    testPersonService()

def testPersonRepository():
    testPersonRepositoryAdd()
    testPersonRepositoryMod()
    testPersonRepositoryGetPersonFromId()

def testPersonRepositoryAdd():
    pRepo = personRepository()
    person0 = person(10, "nume", "adresa")
    pRepo.addPerson(person0)
    assert pRepo.get(0) == person0
    try:
        pRepo.addPerson(person0)
        assert False
    except ValueError:
        assert True

def testPersonRepositoryMod():
    pRepo = personRepository()
    person0 = person(10, "nume", "adresa")
    person1 = person(11, "nume1", "adresa1")
    pRepo.addPerson(person0)
    pRepo.modPerson(person0, person1)
    assert pRepo.get(0) == person1
    person2 = person(10, "nume", "adresa")
    pRepo.addPerson(person2)
    person3 = person(10, "nume2", "adresa2")
    try:
        pRepo.modPerson(person1, person3)
        assert False
    except ValueError:
        assert True

def testPersonRepositoryGetPersonFromId():
    pRepo = personRepository()
    person0 = person(10, "nume", "adresa")
    pRepo.addPerson(person0)
    assert pRepo.getPersonFromId(10) == person0
    try:
        pRepo.getPersonFromId(11)
        assert False
    except ValueError:
        assert True


def testPersonValidator():
    person0 = person(10, "nume", "adresa")
    v = validator()
    v.validate(person0)
    person1 = person(-1, "nume", "adresa")
    try:
        v.validate(person1)
        assert False
    except ValueError:
        assert True
    person2 = person("a", "nume", "adresa")
    try:
        v.validate(person2)
        assert False
    except ValueError:
        assert True

def testPersonService():
    testPersonServiceAdd()
    testPersonServiceMod()

def testPersonServiceAdd():
    pRepo = personRepository()
    v = validator()
    pService = personService(pRepo, v)
    pService.addPerson(10, "nume", "adresa")
    assert pRepo.get(0) == person(10, "nume", "adresa")

def testPersonServiceMod():
    pRepo = personRepository()
    v = validator()
    pService = personService(pRepo, v)
    pService.addPerson(10, "nume", "adresa")
    pService.modPerson(10, 11, "nume1", "adresa1")
    assert pRepo.get(0) == person(11, "nume1", "adresa1")


