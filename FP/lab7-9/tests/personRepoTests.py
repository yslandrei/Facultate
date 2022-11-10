from repositories.personRepository import personRepository
from service.person import person

def testAddPerson():
    pList = personRepository()
    person1 = person(1, "nume1", "adresa1")
    pList.addPerson(person1)
    assert pList.get(0) == person1

def testPopPerson():
    pList = personRepository()
    person1 = person(1, "nume1", "adresa1")
    person2 = person(2, "nume2", "adresa2")
    pList.addPerson(person1)
    pList.addPerson(person2)
    pList.popPerson(person1.getId())
    assert pList.get(0) == person2

def testModPerson():
    pList = personRepository()
    person1 = person(1, "nume1", "adresa1")
    person2 = person(2, "nume2", "adresa2")
    pList.addPerson(person1)
    pList.modPerson(person1.getId(), person2)
    assert pList.get(0) == person2

def testSearchPerson():
    person1 = person(1, "nume1", "adresa1")
    keyword = "adre"
    assert person1.search(keyword)

def testPersonRepo():
    testAddPerson()
    testPopPerson()
    testModPerson()
    testSearchPerson()