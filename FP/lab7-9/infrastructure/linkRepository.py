class linkRepository:
    def __init__(self):
        self.__lList = []

    def addLink(self, link):
        for i in range(len(self.__lList)):
            if self.__lList[i] == link:
                raise ValueError("Persoana participa deja la acest eveniment!\n")
        self.__lList.append(link)

    def popLinksRelatedToPerson(self, Person):
        i = 0
        while i < len(self.__lList):
            if self.__lList[i].getPerson() == Person:
                self.__lList.pop(i)
            else:
                i += 1

    def popLinksRelatedToEvent(self, Event):
        i = 0
        while i < len(self.__lList):
            if self.__lList[i].getEvent() == Event:
                self.__lList.pop(i)
            else:
                i += 1

    def get(self, i):
        return self.__lList[i]

    def __len__(self):
        return len(self.__lList)