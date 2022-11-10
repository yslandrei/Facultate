from repositories.eventRepository import eventRepository
from repositories.linkRepository import linkRepository
from repositories.personRepository import personRepository
from service.event import event
from service.person import person
from service.link import link

def validateEntityIsAlreadyInRepository(repo, entity):
    if type(repo) == personRepository and type(entity) == person:
        validatePersonIsAlreadyInRepository(repo, entity)
    elif type(repo) == eventRepository and type(entity) == event:
        validateEventIsAlreadyInRepository(repo, entity)
    elif type(repo) == linkRepository and type(entity) == link:
        validateLinkIsAlreadyInRepository(repo, entity)

def validatePersonIsAlreadyInRepository(pRepo, newPerson):
    for i in range(len(pRepo)):
        if pRepo.get(i).getId() == newPerson.getId():
            raise ValueError("ID-ul este deja existent!")
        if pRepo.get(i).getName() == newPerson.getName():
            raise ValueError("Numele este deja existent!")

def validateEventIsAlreadyInRepository(eRepo, newEvent):
    for i in range(len(eRepo)):
        if eRepo.get(i).getId() == newEvent.getId():
            raise ValueError("ID-ul este deja existent!")
        if eRepo.get(i).getName() == newEvent.getName():
            raise ValueError("Numele este deja existent!")

def validateLinkIsAlreadyInRepository(lRepo, newLink):
    for i in range(len(lRepo)):
        if lRepo.get(i) == newLink:
            raise ValueError("Persoana este deja inscrisa la acest eveniment!")
    
