def validatePerson(Person):
    errors = ""
    if int(Person.getId()) < 0:
        errors += "ID invalid!\n"
    if Person.getName() == "":
        errors += "Nume invalid!\n"
    if Person.getAdress() == "":
        errors += "Adresa invalida!\n"
    if len(errors):
        raise ValueError(errors)