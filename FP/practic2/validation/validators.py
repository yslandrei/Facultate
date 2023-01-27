def validateTruck(id, name, price, model, date):
    '''
    valideaza daca un tractor are datele valide
    '''
    for digit in id:
        if not digit in '0123456789':
            raise ValueError('ID-ul trebuie sa fie integer')

    for digit in price:
        if not digit in '0123456789':
            raise ValueError('Pretul trebuie sa fie integer')

    if date[2] != ':' or date[5] != ':':
        raise ValueError('Format data gresit') 
    
    day, month, year = date.split(':')

    if len(day) != 2 or len(month) != 2 or len(year) != 4:
        raise ValueError('Format data gresit')

    for digit in day:
        if not digit in '0123456789':
            raise ValueError('Format data gresit')

    for digit in month:
        if not digit in '0123456789':
            raise ValueError('Format data gresit')

    for digit in year:
        if not digit in '0123456789':
            raise ValueError('Format data gresit')

def validateDigit(digit):
    '''
    valideaza daca digit este o cifra
    '''
    if not digit in '0123456789':
        raise ValueError('Introduceti o cifra')

def validateFilters(nameFilter, priceFilter):
    '''
    valideaza filtrele active
    '''
    if priceFilter == '-1':
        return
    for digit in priceFilter:
        if not digit in '0123456789':
            raise ValueError('Filtrul de pret trebuie sa fie integer')