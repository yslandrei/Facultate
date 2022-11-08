class person:
    def __init__(self, id, name, adress):
        self.__id = id
        self.__name = name
        self.__adress = adress

    def getId(self):
        return self.__id
    
    def getName(self):
        return self.__name

    def getAdress(self):
        return self.__adress

    def set(self, newEvent):
        self.__id = newEvent.getId()
        self.__name = newEvent.getName()
        self.__adress = newEvent.getAdress()

    def __str__(self):
        return f"{self.__name}(id: {self.__id}, adresa: {self.__adress})"

    def __eq__(self, other):
        return self.__id == other.__id and self.__name == other.__name and self.__adress == other.__adress 

    def search(self, keyword):
        __result = 0
        if self.__name.find(keyword) != -1:
            __result = 1
        elif self.__adress.find(keyword) != -1:
            __result = 1
        elif str(self.__id).find(keyword) != -1:
            __result = 1
        return __result
            

