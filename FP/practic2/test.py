from datetime import date

def isExpired(tDate):
    tDay, tMonth, tYear = tDate.split(':')
    year, month, day = str(date.today()).split('-')

    if tYear < year:
        return True
    elif tYear > year:
        return False
    else:
        if tMonth < month:
            return True
        elif tMonth > month:
            return False
        else:
            if tDay <= day:
                return True
            elif tDay > day:
                return False

print(isExpired('21:06:2022'))