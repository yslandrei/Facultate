from domain.link import link
from domain.event import event
from domain.person import person


class validator():
    def validate(self, entity):
        if type(entity) == person:
            self.validatePerson(entity)
        elif type(entity) == event:
            self.validateEvent(entity)
        elif type(entity) == link:
            self.validateLink(entity)

    def validatePerson(self, Person):
        errors = ""
        if int(Person.getId()) < 0:
            errors += "ID invalid!\n"
        if Person.getName() == "":
            errors += "Nume invalid!\n"
        if Person.getAdress() == "":
            errors += "Adresa invalida!\n"
        if len(errors):
            raise ValueError(errors)

    def validateEvent(self, Event):
        errors = ""
        if int(Event.getId()) < 0:
            errors += "ID invalid!\n"
        if Event.getName() == "":
            errors += "Nume invalid!\n"
        if Event.getDate() == "":
            errors += "Data invalida!\n"
        if Event.getTime() == "":
            errors += "Data invalida!\n"
        if len(errors):
            raise ValueError(errors)

    def validateLink(self, Link):
        pass