from repositories.linkRepository import linkRepository
from service.event import event
from service.person import person
from service.link import link


def testAddLink():
    lList = linkRepository()
    person1 = person(1, "nume1", "adresa1")
    event1 = event(10, "nume1", "data1", "timp1")
    link1 = link(person1, event1)
    lList.addLink(link1)
    assert lList.get(0).getPerson() == person1 and lList.get(0).getEvent() == event1

def testLinkRepo():
    testAddLink()