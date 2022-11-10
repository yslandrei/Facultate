from tests.personRepoTests import testPersonRepo
from tests.eventRepoTests import testEventRepo
from tests.linkRepoTests import testLinkRepo
from tests.validateRepoTests import testValidateRepo


def runAllTests():
    testPersonRepo()
    testEventRepo()
    testLinkRepo()
    testValidateRepo()