from domain.person import person
from domain.event import event
from domain.link import link


class linkFileRepository:
    def __init__(self):
        self.__fileName = "infrastructure\linkData.txt"
        self.__lList = []
        self.loadFile()

    def addLink(self, link):
        for i in range(len(self.__lList)):
            if self.__lList[i] == link:
                raise ValueError("Persoana participa deja la acest eveniment!\n")
        self.__lList.append(link)

    def popLink(self, Link):
        for i in range(len(self.__lList)):
            if self.__lList[i] == Link:
                self.__lList.pop(i)
                break

    def get(self, i):
        return self.__lList[i]

    def __len__(self):
        return len(self.__lList)

    def loadFile(self):
        with open(self.__fileName, "r") as f:
            for line in f:
                args = line.strip("\n").split(", ")
                Person = person(int(args[0]), args[1], args[2])
                Event = event(int(args[3]), args[4], args[5], args[6])
                Link = link(Person, Event)
                self.__lList.append(Link)

    def saveFile(self):
        with open(self.__fileName, "w") as f:
            for link in self.__lList:
                line = str(link.getPerson().getId()) + ", " + link.getPerson().getName() + ", " + link.getPerson().getAdress() + ", " + str(link.getEvent().getId()) + ", " + link.getEvent().getName() + ", " + link.getEvent().getDate() + ", " + link.getEvent().getTime() + "\n"
                f.write(line)