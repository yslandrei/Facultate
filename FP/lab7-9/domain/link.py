class link:
    def __init__(self, Person, Event):
        self.__person = Person
        self.__event = Event
    
    def getPerson(self):
        return self.__person

    def getEvent(self):
        return self.__event
    
    def __eq__(self, other):
        return self.getPerson() == other.getPerson() and self.getEvent() == other.getEvent()

    def __str__(self):
        return f"{self.getPerson()} ➜  {self.getEvent()}"