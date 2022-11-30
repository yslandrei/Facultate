from domain.event import event


class eventService():
    def __init__(self, eRepo, v):
        self.__eRepo = eRepo
        self.__v = v

    def addEvent(self, id, name, date, time):
        Event = event(id, name, date, time)
        self.__v.validate(Event)
        self.__eRepo.addEvent(Event)

    def modEvent(self, id, nId, nName, nDate, nTime):
        newEvent = event(nId, nName, nDate, nTime)
        self.__v.validate(newEvent)
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

    def saveFile(self):
        self.__eRepo.saveFile()
