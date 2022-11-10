def validateId(id):
    if id < 0:
        raise ValueError("Introduceti un ID pozitiv!")

def validateIdInRepository(repo, id):
    for i in range(len(repo)):
        if repo.get(i).getId() == id:
            return
    raise ValueError("ID-ul nu exista in lista!")

def validateIdIsAlreadyInRepository(repo, nId, id):
    if nId == id:
        return
    for i in range(len(repo)):
        if repo.get(i).getId() == nId:
            raise ValueError("Noul ID exista deja in lista!")