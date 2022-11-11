def validateEvent(Event):
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