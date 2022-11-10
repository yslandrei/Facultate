from repositories.eventRepository import eventRepository
from service.event import event

 
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

def testEventRepo():
    testAddEvent()
    testPopEvent()
    testModEvent()
    testSearchEvent()
