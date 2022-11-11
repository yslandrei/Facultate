from domain.event import event
from validation.eventValidator import validateEvent


class eventService():
    def __init__(self, eRepo, lRepo):
        self.__eRepo = eRepo
        self.__lRepo = lRepo

    def addEvent(self, id, name, date, time):
        Event = event(id, name, date, time)
        validateEvent(Event)
        self.__eRepo.addEvent(Event)

    def popEvent(self, id):
        Event = self.__eRepo.getEventFromId(id)
        self.__eRepo.popEvent(Event)
        self.__lRepo.popLinksRelatedToEvent(Event)

    def modEvent(self, id, nId, nName, nDate, nTime):
        newEvent = event(nId, nName, nDate, nTime)
        validateEvent(newEvent)
        oldEvent = self.__eRepo.getEventFromId(id)
        self.__eRepo.modEvent(oldEvent, newEvent)

    def srcEvent(self, keyword):
        result = ""
        for i in range(len(self.__eRepo)):
            if str(self.__eRepo.get(i).getId()).find(keyword) != -1:
                result = result + str(self.__eRepo.get(i)) + "\n"
            elif self.__eRepo.get(i).getName().find(keyword) != -1:
                result = result + str(self.__eRepo.get(i)) + "\n"
            elif self.__eRepo.get(i).getDate().find(keyword) != -1:
                result = result + str(self.__eRepo.get(i)) + "\n"
            elif self.__eRepo.get(i).getTime().find(keyword) != -1:
                result = result + str(self.__eRepo.get(i)) + "\n"
        if len(result):
            print(result, end = '')
        else:
            print("Niciun rezultat gasit!\n") 

    def printAll(self):
        for i in range(len(self.__eRepo)):
            if i + 1 != len(self.__eRepo):
                print(f" ├─ {self.__eRepo.get(i)}")
            else:
                print(f" └─ {self.__eRepo.get(i)}")
