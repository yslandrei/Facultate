from repositories.eventRepository import eventRepository
from repositories.linkRepository import linkRepository
from repositories.personRepository import personRepository
from service.event import event
from service.person import person
from service.link import link


def printMenu():
    print("• Adauga persoana in lista                                          - addP [id], [nume], [adresa]")
    print("• Sterge persoana din lista                                         - popP [id]")
    print("• Modifica persoana din lista                                       - modP [id], [nId], [nNume], [nAdresa]")
    print("• Cauta persoana in lista                                           - srcP [keyword]")
    print("• Adauga eveniment in lista                                         - addE [id], [nume], [data], [timp]")
    print("• Sterge eveniment din lista                                        - popE [id]")
    print("• Modifica eveniment din lista                                      - modE [id], [nId], [nNume], [nData], [nTimp]")
    print("• Cauta eveniment in lista                                          - srcE [keyword]")
    print("• Inscrie persoana la eveniment                                     - link [pId], [eId]")
    print("• Afiseaza evenimentele la care participa o persoana ordonate dupa  - ppes [pId]")
    print("  nume si data")
    print("• Afiseaza persoanele participante la cele mai multe evenimente     - pmep")
    print("• Afiseaza primele 20% din evenimente cu cei mai multi participanti - pmpe")

def clearScreen():
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

def printAllLists(pList, eList, lList):
    print("📁 Persoane:")
    pList.printAll()
    print("\n📁 Evenimente:")
    eList.printAll()
    print("\n📁 Participari:")
    lList.printAll()
    print("\n")

def loadLists(pList, eList, lList):
    andrei = person(0, "Andrei Diaconescu", "Valcea")
    teodor = person(1, "Teodor Domnica", "Prahova")
    ivancu = person(2, "Andrei Ivancu", "Valcea")
    rares = person(3, "Rares Bozga", "Satu Mare")
    pList.addPerson(andrei)
    pList.addPerson(teodor)
    pList.addPerson(ivancu)
    pList.addPerson(rares)
    untold = event(10, "Untold", "04.08.2023", "4 zile")
    electric = event(11, "Electric Castle", "13.07.2023", "3 zile")
    hustle = event(12, "Hustle", "01.12.2022", "2 zile")
    neversea = event(13, "Neversea", "15.08.2023", "3 zile")
    saga = event(14, "Saga", "28.08.2023", "2 zile")
    eList.addEvent(untold)
    eList.addEvent(electric)
    eList.addEvent(hustle)
    eList.addEvent(neversea)
    eList.addEvent(saga)
    link0 = link(andrei, untold)
    link1 = link(andrei, electric)
    link2 = link(andrei, hustle)
    link3 = link(teodor, electric)
    link4 = link(teodor, untold)
    link5 = link(teodor, neversea)
    link6 = link(ivancu, untold)
    link7 = link(ivancu, electric)
    link8 = link(rares, untold)
    link9 = link(rares, saga)
    lList.addLink(link0)
    lList.addLink(link1)
    lList.addLink(link2)
    lList.addLink(link3)
    lList.addLink(link4)
    lList.addLink(link5)
    lList.addLink(link6)
    lList.addLink(link7)
    lList.addLink(link8)
    lList.addLink(link9)

def runMenu():
    pList = personRepository()
    eList = eventRepository()
    lList = linkRepository()
    loadLists(pList, eList, lList)
    clearScreen()
    while(True):
        printMenu()
        command = input("\nIntroduceti Comanda(a = afis liste, q = quit):")
        clearScreen()
        if command == "q":
            return
        elif command == "a":
            printAllLists(pList, eList, lList)
        elif command[:4] == "addP":
            try:
                id, name, adress = command[5:].split(", ")
                newPerson = person(int(id), name, adress)
                pList.addPerson(newPerson)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "popP":
            try:
                id = command[5:]
                pList.popPerson(int(id))
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "modP":
            try:
                id, nId, nName, nAdress = command[5:].split(", ")
                newPerson = person(int(nId), nName, nAdress)
                pList.modPerson(int(id), newPerson)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "srcP":
            try:
                keyword = command[5:]
                pList.searchPerson(keyword)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "addE":
            try:
                id, name, date, time = command[5:].split(", ")
                newEvent = event(int(id), name, date, time)
                eList.addEvent(newEvent)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "popE":
            try:
                id = command[5:]
                eList.popEvent(int(id))
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "modE":
            try:
                id, nId, nName, nDate, nTime = command[5:].split(", ")
                newEvent = event(int(nId), nName, nDate, nTime)
                eList.modEvent(int(id), newEvent)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "srcE":
            try:
                keyword = command[5:]
                eList.searchEvent(keyword)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "link":
            try:
                pId, eId = command[5:].split(", ")
                lPerson = pList.getPersonFromId(int(pId))
                lEvent = eList.getEventFromId(int(eId))
                newLink = link(lPerson, lEvent)
                lList.addLink(newLink)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "ppes":
            try:
                id = command[5:]
                lPerson = pList.getPersonFromId(int(id))
                lList.printPersonsEvents(lPerson)
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "pmep":
            try:
                lList.printMostEventsAPersonParticipates()
            except ValueError:
                print("Sintaxa Invalida!")
        elif command[:4] == "pmpe":
            try:
                lList.printMostParticipatedEvents()
            except ValueError:
                print("Sintaxa Invalida!")    
        else:
            print("Comanda Invalida!")