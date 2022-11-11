class eventRepository:
    def __init__(self):
        self.__eList = []

    def get(self, i):
        return self.__eList[i]

    def __len__(self):
        return len(self.__eList)

    def addEvent(self, event):
        for i in range(len(self.__eList)):
            if self.__eList[i].getId() == event.getId():
                raise ValueError("ID deja existent!\n")
        self.__eList.append(event)

    def popEvent(self, Event):
        for i in range(len(self.__eList)):
            if self.__eList[i].getId() == Event.getId():
                self.__eList.pop(i)
                break
    
    def modEvent(self, oldEvent, newEvent):
        for i in range(len(self.__eList)):
            if self.__eList[i].getId() == newEvent.getId() and oldEvent.getId() != newEvent.getId():
                raise ValueError("Noul ID deja existent!\n")
        for i in range(len(self.__eList)):
            if self.__eList[i].getId() == oldEvent.getId():
                self.__eList[i].set(newEvent)
                break

    def getEventFromId(self, id):
        for i in range(len(self.__eList)):
             if self.__eList[i].getId() == id:
                return self.__eList[i]
        raise ValueError("ID inexistent!\n")