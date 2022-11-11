import copy
from domain.link import link
from validation.linkValidator import validateLink


class linkService():
    def __init__(self, pRepo, eRepo, lRepo):
        self.__pRepo = pRepo
        self.__eRepo = eRepo
        self.__lRepo = lRepo

    def addLink(self, pId, eId):
        Person = self.__pRepo.getPersonFromId(pId)
        Event = self.__eRepo.getEventFromId(eId)
        Link = link(Person, Event)
        validateLink(Link)
        self.__lRepo.addLink(Link)

    def printAll(self):
        for i in range(len(self.__lRepo)):
            if i + 1 != len(self.__lRepo):
                print(f" ├─ {self.__lRepo.get(i)}")
            else:
                print(f" └─ {self.__lRepo.get(i)}")    

    def printPersonsEvents(self, id):
        Person = self.__pRepo.getPersonFromId(id)
        personsEvents = []
        for i in range(len(self.__lRepo)):
            if self.__lRepo.get(i).getPerson() == Person:
                personsEvents.append(self.__lRepo.get(i).getEvent())
        personsEvents = sorted(personsEvents, key = lambda x: (x.getName(), x.getDate()))
        if len(personsEvents):
            print(f"{Person} ➜  {len(personsEvents)} evenimente:\n") if len(personsEvents) != 1 else print(f"{len(personsEvents)} eveniment:\n")
            for _event in personsEvents:
                print(_event)
            print()

    def printMostEventsAPersonParticipates(self):
        max = 0
        pFreq = [0 for _ in range(1000)]
        maxPeople = []
        for i in range(len(self.__lRepo)):
            pFreq[self.__lRepo.get(i).getPerson().getId()] += 1
            if pFreq[self.__lRepo.get(i).getPerson().getId()] > max:
                max = pFreq[self.__lRepo.get(i).getPerson().getId()]
                maxPeople.clear()
                maxPeople.append(self.__lRepo.get(i).getPerson())
            elif pFreq[self.__lRepo.get(i).getPerson().getId()] == max:
                maxPeople.append(self.__lRepo.get(i).getPerson())
        if max:
            for _person in maxPeople:
                print(f"{_person} ➜  {max} evenimente") if max != 1 else print(f"{_person} ➜  {max} eveniment")
            print()

    def printMostParticipatedEvents(self):
        __dict = {
            "event": 0,
            "freq": 0
        }
        eFreq = [copy.deepcopy(__dict) for _ in range(1000)]
        eventsLen = 0
        for i in range(len(self.__lRepo)):
            if eFreq[self.__lRepo.get(i).getEvent().getId()]["freq"] == 0:
                eventsLen += 1
            eFreq[self.__lRepo.get(i).getEvent().getId()]["freq"] += 1
            eFreq[self.__lRepo.get(i).getEvent().getId()]["event"] = self.__lRepo.get(i).getEvent()
        eFreq = sorted(eFreq, key = lambda x: x["freq"], reverse = True)
        firstFifthLen = int(eventsLen * .2)
        if firstFifthLen:
            print(f"{firstFifthLen} = 20% din {eventsLen} evenimente totale:\n") if eventsLen != 1 else print(f"{firstFifthLen} = 20% din {len(eventsLen)} eveniment total:\n")
            for i in range(firstFifthLen):
                Event = eFreq[i]["event"]
                Freq = eFreq[i]["freq"]
                print(f"{Event.getName()}(id: {Event.getId()}, data: {Event.getDate()}, timp: {Event.getTime()}) ➜  nr participanti: {Freq}")
            print()
        
        
