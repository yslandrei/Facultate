class event:
    def __init__(self, id, name, date, time):
        self.__id = id
        self.__name = name
        self.__date = date
        self.__time = time

    def getId(self):
        return self.__id
    
    def getDate(self):
        return self.__date

    def getTime(self):
        return self.__time

    def getName(self):
        return self.__name

    def get(self):
        return self

    def set(self, newEvent):
        self.__id = newEvent.getId()
        self.__name = newEvent.getName()
        self.__date = newEvent.getDate()
        self.__time = newEvent.getTime()

    def __str__(self):
        return f"{self.__name}(id: {self.__id}, data: {self.__date}, timp: {self.__time})"

    def __eq__(self, other):
        return self.__id == other.__id and self.__name == other.__name and self.__date == other.__date and self.__time == other.__time 

    def __lt__(self, other):
        if self.__name == other.__name:
            return self.__date < other.__date
        else:
            return self.__name < other.__name

    def search(self, keyword):
        __result = 0
        if self.__name.find(keyword) != -1:
            __result = 1
        elif self.__date.find(keyword) != -1:
            __result = 1
        elif self.__time.find(keyword) != -1:
            __result = 1
        elif str(self.__id).find(keyword) != -1:
            __result = 1
        return __result

    def getEventPositionInFreqList(self, __eFreq):
        for i in range(len(__eFreq)):
            if __eFreq[i]["event"] == self:
                return i
        return -1
        

