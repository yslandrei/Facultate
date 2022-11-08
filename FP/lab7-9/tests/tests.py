from service.event import event
from service.person import person
from service.link import link
from repositories.eventRepository import eventRepository
from repositories.personRepository import personReporitory
from repositories.linkRepository import linkRepository

def runTests():
    testAddEvent()
    testPopEvent()
    testModEvent()
    testSearchEvent()
    testAddPerson()
    testPopPerson()
    testModPerson()
    testSearchPerson()
    testAddLink()

def testAddEvent():
    eList = eventRepository()
    event1 = event(1, "nume1", "data1", "timp1")
    eList.addEvent(event1)
    assert eList.get(0) == event1

def testPopEvent():
    eList = eventRepository()
    event1 = event(1, "nume1", "data1", "timp1")
    event2 = event(2, "nume2", "data2", "timp2")
    eList.addEvent(event1)
    eList.addEvent(event2)
    eList.popEvent(event1.getId())
    assert eList.get(0) == event2

def testModEvent():
    eList = eventRepository()
    event1 = event(1, "nume1", "data1", "timp1")
    event2 = event(2, "nume2", "data2", "timp2")
    eList.addEvent(event1)
    eList.modEvent(event1.getId(), event2)
    assert eList.get(0) == event2

def testSearchEvent():
    event1 = event(1, "nume1", "data1", "timp1")
    keyword = "num"
    assert event1.search(keyword)

def testAddPerson():
    pList = personReporitory()
    person1 = person(1, "nume1", "adresa1")
    pList.addPerson(person1)
    assert pList.get(0) == person1

def testPopPerson():
    pList = personReporitory()
    person1 = person(1, "nume1", "adresa1")
    person2 = person(2, "nume2", "adresa2")
    pList.addPerson(person1)
    pList.addPerson(person2)
    pList.popPerson(person1.getId())
    assert pList.get(0) == person2

def testModPerson():
    pList = personReporitory()
    person1 = person(1, "nume1", "adresa1")
    person2 = person(2, "nume2", "adresa2")
    pList.addPerson(person1)
    pList.modPerson(person1.getId(), person2)
    assert pList.get(0) == person2

def testSearchPerson():
    person1 = person(1, "nume1", "adresa1")
    keyword = "adre"
    assert person1.search(keyword)

def testAddLink():
    lList = linkRepository()
    person1 = person(1, "nume1", "adresa1")
    event1 = event(10, "nume1", "data1", "timp1")
    link1 = link(person1, event1)
    lList.addLink(link1)
    assert lList.get(0).getPerson() == person1 and lList.get(0).getEvent() == event1
    

    

