import copy
from domain.link import link


class linkService():
    def __init__(self, pRepo, eRepo, lRepo, v):
        self.__pRepo = pRepo
        self.__eRepo = eRepo
        self.__lRepo = lRepo
        self.__v = v

    def addLink(self, pId, eId):
        Person = self.__pRepo.getPersonFromId(pId)
        Event = self.__eRepo.getEventFromId(eId)
        Link = link(Person, Event)
        self.__v.validate(Link)
        self.__lRepo.addLink(Link)

    def popPersonAndLinksRelated(self, id):
        Person = self.__pRepo.getPersonFromId(id)
        self.__pRepo.popPerson(Person)
        i = 0
        while(i < len(self.__lRepo)):
            if Person == self.__lRepo.get(i).getPerson():
                self.__lRepo.popLink(self.__lRepo.get(i))
            else:
                i += 1

    def popEventAndLinksRelated(self, id):
        Event = self.__eRepo.getEventFromId(id)
        self.__pRepo.popPerson(Event)
        i = 0
        while(i < len(self.__lRepo)):
            if Event == self.__lRepo.get(i).getEvent():
                self.__lRepo.popLink(self.__lRepo.get(i))
            else:
                i += 1

    def printAll(self):
        for i in range(len(self.__lRepo)):
            if i + 1 != len(self.__lRepo):
                print(f" ├─ {self.__lRepo.get(i)}")
            else:
                print(f" └─ {self.__lRepo.get(i)}")   

    def saveFile(self):
        self.__pRepo.saveFile()
        self.__eRepo.saveFile()
        self.__lRepo.saveFile()

    def cmpKey(self, a, b):
        return a < b

    def getMinIndexFromArray(self, arr, lft, rgt):
        minIndex = lft
        for i in range(lft, rgt):
            if self.cmpKey(arr[i], arr[minIndex]):
                minIndex = i
        return minIndex

    def selectionSortRec(self, arr, lft, rgt):
        if lft == rgt:
            return
        minIndex = self.getMinIndexFromArray(arr, lft, rgt)
        (arr[lft], arr[minIndex]) = (arr[minIndex], arr[lft])
        self.selectionSortRec(arr, lft + 1, rgt)

    def shakeSort(self, arr):
        sorted = False
        lft = 0
        rgt = len(arr) - 1
        while(sorted == False):
            sorted = True
            for i in range(lft, rgt):
                if self.cmpKey(arr[i + 1], arr[i]):
                    arr[i], arr[i + 1] = arr[i + 1], arr[i]
                    sorted = False

            if sorted == True:
                return
            sorted = True

            rgt = rgt - 1
            for i in range(rgt - 1, lft - 1, -1):
                if self.cmpKey(arr[i + 1], arr[i]):
                    arr[i], arr[i + 1] = arr[i + 1], arr[i]
                    sorted = False
            lft = lft + 1
        return arr

    def getPersonsEvents(self, id):
        Person = self.__pRepo.getPersonFromId(id)
        personsEvents = []
        answear = ""
        for i in range(len(self.__lRepo)):
            if self.__lRepo.get(i).getPerson() == Person:
                personsEvents.append(self.__lRepo.get(i).getEvent())
        #personsEvents = sorted(personsEvents, key = lambda x: (x.getName(), x.getDate()))
        self.selectionSortRec(personsEvents, 0, len(personsEvents))
        #personsEvents = self.shakeSort(personsEvents)
        if len(personsEvents):
            answear = f"{Person} ➜  {len(personsEvents)} evenimente:\n\n" if len(personsEvents) != 1 else f"{len(personsEvents)} eveniment:\n\n"
            for _event in personsEvents:
                answear = answear + str(_event) + "\n"
        return answear

    def getMostEventsAPersonParticipates(self):
        max = 0
        pFreq = [0 for _ in range(1000)]
        maxPeople = []
        answear = ""
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
                answear = answear + f"{_person} ➜  {max} evenimente\n" if max != 1 else f"{_person} ➜  {max} eveniment\n"
        return answear

    def getLeastEventsAPersonParticipates(self):
        max = 99999
        pFreq = [0 for _ in range(1000)]
        maxPeople = []
        answear = ""
        for i in range(len(self.__lRepo)):
            pFreq[self.__lRepo.get(i).getPerson().getId()] += 1
            if pFreq[self.__lRepo.get(i).getPerson().getId()] < max:
                max = pFreq[self.__lRepo.get(i).getPerson().getId()]
                maxPeople.clear()
                maxPeople.append(self.__lRepo.get(i).getPerson())
            elif pFreq[self.__lRepo.get(i).getPerson().getId()] == max:
                maxPeople.append(self.__lRepo.get(i).getPerson())
        if max:
            for _person in maxPeople:
                answear = answear + f"{_person} ➜  {max} evenimente\n" if max != 1 else f"{_person} ➜  {max} eveniment\n"
        return answear

    def getMostParticipatedEvents(self):
        __dict = {
            "event": 0,
            "freq": 0
        }
        eFreq = [copy.deepcopy(__dict) for _ in range(1000)]
        eventsLen = 0
        answear = ""
        for i in range(len(self.__lRepo)):
            if eFreq[self.__lRepo.get(i).getEvent().getId()]["freq"] == 0:
                eventsLen += 1
            eFreq[self.__lRepo.get(i).getEvent().getId()]["freq"] += 1
            eFreq[self.__lRepo.get(i).getEvent().getId()]["event"] = self.__lRepo.get(i).getEvent()
        eFreq = sorted(eFreq, key = lambda x: x["freq"], reverse = True)
        firstFifthLen = int(eventsLen * .2)
        if firstFifthLen:
            answear = f"{firstFifthLen} = 20% din {eventsLen} evenimente totale:\n\n" if eventsLen != 1 else f"{firstFifthLen} = 20% din {len(eventsLen)} eveniment total:\n\n"
            for i in range(firstFifthLen):
                Event = eFreq[i]["event"]
                Freq = eFreq[i]["freq"]
                answear = answear + f"{Event.getName()}(id: {Event.getId()}, data: {Event.getDate()}, timp: {Event.getTime()}) ➜  nr participanti: {Freq}\n"
        return answear

        
        
