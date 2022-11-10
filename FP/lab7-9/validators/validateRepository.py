from repositories.eventRepository import eventRepository
from repositories.linkRepository import linkRepository
from repositories.personRepository import personRepository
from service.event import event
from service.person import person
from service.link import link

def validateRepository(repo, entity):
    if type(repo) == personRepository and type(entity) == person:
        validatePersonRepository(repo, entity)
    elif type(repo) == eventRepository and type(entity) == event:
        validateEventRepository(repo, entity)
    elif type(repo) == linkRepository and type(entity) == link:
        validateLinkRepository(repo, entity)

def validatePersonRepository(pRepo, newPerson):
    for i in range(len(pRepo)):
        if pRepo.get(i).getId() == newPerson.getId():
            raise ValueError("ID-ul este deja existent!")
        if pRepo.get(i).getName() == newPerson.getName():
            raise ValueError("Numele este deja existent!")

def validateEventRepository(eRepo, newEvent):
    for i in range(len(eRepo)):
        if eRepo.get(i).getId() == newEvent.getId():
            raise ValueError("ID-ul este deja existent!")
        if eRepo.get(i).getName() == newEvent.getName():
            raise ValueError("Numele este deja existent!")

def validateLinkRepository(lRepo, newLink):
    for i in range(len(lRepo)):
        if lRepo.get(i) == newLink:
            raise ValueError("Persoana este deja inscrisa la acest eveniment!")

def validateId(id):
    if id < 0:
        raise ValueError("Introduceti un ID pozitiv!")

def validateIdInRepository(repo, id):
    for i in range(len(repo)):
        if repo.get(i).getId() == id:
            return
    raise ValueError("ID-ul nu exista in lista!")

def validateIdIsAlreadyInRepository(repo, id):
    for i in range(len(repo)):
        if repo.get(i).getId() == id:
            raise ValueError("Noul ID exista deja in lista!")
    
