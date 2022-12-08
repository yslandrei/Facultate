from domain.event import event


class eventFileRepository:
    def __init__(self):
        self.__fileName = "infrastructure\eventData.txt"
        self.__eList = []
        self.loadFile()

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

    def loadFile(self):
        with open(self.__fileName, "r") as f:
            for line in f:
                args = line.strip("\n").split(", ")
                Event = event(int(args[0]), args[1], args[2], args[3])
                self.__eList.append(Event)

    def saveFile(self):
        with open(self.__fileName, "w") as f:
            for event in self.__eList:
                line = str(event.getId()) + ", " + event.getName() + ", " + event.getDate() + ", " + event.getTime() + "\n"
                f.write(line)