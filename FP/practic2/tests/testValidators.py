from validation.validators import validateDigit, validateFilters, validateTruck

def testValidators():
    testValidateTruck()
    testValidateDigit()
    testValidateFilters()

def testValidateTruck():
    try:
        validateTruck('a', 'test', '1234', 'test', '10:10:2000')
        assert False
    except ValueError:
        assert True

    try:
        validateTruck('1', 'test', '123a', 'test', '10:10:2000')
        assert False
    except ValueError:
        assert True

    try:
        validateTruck('1', 'test', '1234', 'test', '10.10:2000')
        assert False
    except ValueError:
        assert True

    validateTruck('0', 'test', '1234', 'test', '10:10:2000')

def testValidateDigit():
    try:
        validateDigit('a')
        assert False
    except ValueError:
        assert True

    validateDigit('1')

def testValidateFilters():
    try:
        validateFilters('test', 'a234')
        assert False
    except ValueError:
        assert True

    validateFilters('test', '1234')
