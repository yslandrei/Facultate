from tests.testEventFunctionalities import testAllEventFunctionalities
from tests.testPersonFunctionalities import testAllPersonFunctionalities
from tests.testLinkFunctionalities import testAllLinkFunctionalities


def runAllTests():
    testAllEventFunctionalities()
    testAllPersonFunctionalities()
    testAllLinkFunctionalities()