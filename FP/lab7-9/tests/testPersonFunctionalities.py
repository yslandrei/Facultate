from domain.person import person
from infrastructure.personRepository import personRepository
from infrastructure.linkRepository import linkRepository
from validation.personValidator import validatePerson
from buisness.personService import personService


def testAllPersonFunctionalities():
    testPersonRepository()
    testPersonValidator()
    testPersonService()

def testPersonRepository():
    testPersonRepositoryAdd()
    testPersonRepositoryPop()
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

def testPersonRepositoryPop():
    pRepo = personRepository()
    person0 = person(10, "nume", "adresa")
    pRepo.addPerson(person0)
    pRepo.popPerson(person0)
    assert len(pRepo) == 0

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
    validatePerson(person0)
    person1 = person(-1, "nume", "adresa")
    try:
        validatePerson(person1)
        assert False
    except ValueError:
        assert True
    person2 = person("a", "nume", "adresa")
    try:
        validatePerson(person2)
        assert False
    except ValueError:
        assert True

def testPersonService():
    testPersonServiceAdd()
    testPersonServicePop()
    testPersonServiceMod()

def testPersonServiceAdd():
    pRepo = personRepository()
    lRepo = linkRepository()
    pService = personService(pRepo, lRepo)
    pService.addPerson(10, "nume", "adresa")
    assert pRepo.get(0) == person(10, "nume", "adresa")

def testPersonServicePop():
    pRepo = personRepository()
    lRepo = linkRepository()
    pService = personService(pRepo, lRepo)
    pService.addPerson(10, "nume", "adresa")
    pService.popPerson(10)
    assert len(pRepo) == 0

def testPersonServiceMod():
    pRepo = personRepository()
    lRepo = linkRepository()
    pService = personService(pRepo, lRepo)
    pService.addPerson(10, "nume", "adresa")
    pService.modPerson(10, 11, "nume1", "adresa1")
    assert pRepo.get(0) == person(11, "nume1", "adresa1")


