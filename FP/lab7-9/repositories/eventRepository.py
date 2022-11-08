class eventRepository:
    def __init__(self):
        self.__eList = []

    def get(self, i):
        return self.__eList[i]

    def addEvent(self, event):
        self.__eList.append(event)
    
    def popEvent(self, id):
        i = 0
        while i < len(self.__eList):
            if self.__eList[i].getId() == id:
                self.__eList.pop(i)
            else:
                i += 1
    
    def modEvent(self, id, newEvent):
        for i in range(len(self.__eList)):
            if self.__eList[i].getId() == id:
                self.__eList[i].set(newEvent)

    def getEventFromId(self, id):
        for i in range(len(self.__eList)):
             if self.__eList[i].getId() == id:
                return self.__eList[i]

    def searchEvent(self, keyword):
        for i in range(len(self.__eList)):
            if self.__eList[i].search(keyword):
                print(self.__eList[i])

    def printAll(self):
        for __event in self.__eList:
            if __event != self.__eList[-1]:
                print(f" ┣ {__event}")
            else:
                print(f" ┗ {__event}")
