class linkRepository:
    def __init__(self):
        self.__lList = []

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