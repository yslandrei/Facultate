import unittest
from domain.person import person
from buisness.personService import personService
from validation.validator import validator
from infrastructure.personRepository import personRepository

class testEventPerson(unittest.TestCase):
    def setUp(self):
        self.pRepo = personRepository()
        self.v = validator()
        self.pService = personService(self.pRepo, self.v)
        self.pService.addPerson(0, "person0", "adress0")
        self.pService.addPerson(1, "person1", "adress1")
        self.pService.addPerson(2, "person2", "adress2")
        self.pService.addPerson(3, "person3", "adress3")

    def testAdd(self):
        self.pService.addPerson(4, "person4", "adress4")
        self.assertEqual(self.pRepo.get(4), person(4, "person4", "adress4"))
   
    def testMod(self):
        self.pService.modPerson(2, 2, "personmod", "adress3")
        self.assertEqual(self.pRepo.get(2), person(2, "personmod", "adress3"))