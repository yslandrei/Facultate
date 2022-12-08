import unittest
from domain.event import event
from buisness.eventService import eventService
from validation.validator import validator
from infrastructure.eventRepository import eventRepository

class testEventService(unittest.TestCase):
    def setUp(self):
        self.eRepo = eventRepository()
        self.v = validator()
        self.eService = eventService(self.eRepo, self.v)
        self.eService.addEvent(10, "event0", "date0", "time0")
        self.eService.addEvent(11, "event1", "date1", "time1")
        self.eService.addEvent(12, "event2", "date2", "time2")
        self.eService.addEvent(13, "event3", "date3", "time3")

    def testAdd(self):
        self.eService.addEvent(14, "event4", "date4", "time4")
        self.assertEqual(self.eRepo.get(4), event(14, "event4", "date4", "time4"))
   
    def testMod(self):
        self.eService.modEvent(12, 12, "eventmod", "date3", "time3")
        self.assertEqual(self.eRepo.get(2), event(12, "eventmod", "date3", "time3"))

if __name__ == '__main__':
    unittest.main()