from math import ceil


class linkRepository:
    def __init__(self):
        self.__lList = []

    def addLink(self, link):
        self.__lList.append(link)

    def get(self, i):
        return self.__lList[i]

    def printAll(self):
        for __link in self.__lList:
            if __link != self.__lList[-1]:
                print(f" ┣ {__link}")
            else:
                print(f" ┗ {__link}")

    def printPersonsEvents(self, __person):
        __pEvents = []
        for i in range(len(self.__lList)):
            if self.__lList[i].getPerson() == __person:
                __pEvents.append(self.__lList[i].getEvent())
        __pEvents.sort()
        if len(__pEvents):
            print(f"{len(__pEvents)} evenimente:\n") if len(__pEvents) != 1 else print(f"{len(__pEvents)} eveniment:\n")
            for __event in __pEvents:
                print(__event)
            print("\n")

    def printMostEventsAPersonParticipates(self):
        __max = 0
        __pFreq = [0 for _ in range(100)]
        __mPeople = []
        for __link in self.__lList:
            __pFreq[__link.getPerson().getId()] += 1
            if __pFreq[__link.getPerson().getId()] > __max:
                __max = __pFreq[__link.getPerson().getId()]
                __mPeople.clear()
                __mPeople.append(__link.getPerson())
            elif __pFreq[__link.getPerson().getId()] == __max:
                __mPeople.append(__link.getPerson())
        if __max:
            print(f"{__max} evenimente:\n") if __max != 1 else print(f"{__max} eveniment:\n")
            for __person in __mPeople:
                print(__person)
            print("\n")

    def printMostParticipatedEvents(self):
        __eFreq = []
        for __link in self.__lList:
            __ePos = __link.getEvent().getEventPositionInFreqList(__eFreq)
            if __ePos != -1:
                __eFreq[__ePos]["freq"] += 1
            else:
                __eFreq.append({"event": __link.getEvent(), "freq": 1})
        __eFreq = sorted(__eFreq, key = lambda x: x["freq"], reverse = True)
        __lenFirstFifth = ceil(len(__eFreq) * .2)
        if __lenFirstFifth:
            print(f"{__lenFirstFifth} = 20% din {len(__eFreq)} evenimente totale:\n") if len(__eFreq) != 1 else print(f"{__lenFirstFifth} = 20% din {len(__eFreq)} eveniment total:\n")
            for i in range(__lenFirstFifth):
                __event = __eFreq[i]["event"]
                __freq = __eFreq[i]["freq"]
                print(f"{__event.getName()}(id: {__event.getId()}, data: {__event.getDate()}, timp: {__event.getTime()}, nr participanti: {__freq})")
            print("\n")

        
        

