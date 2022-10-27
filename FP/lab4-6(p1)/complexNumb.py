import math


class complexNumb:
    """
    Clasa pentru numere complexe
    numar = a + bi
    a, b - partea reala/imaginara a numarului
    """
    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __str__(self):
        """
        print(complexNumb(1,2))
        Tipareste numarul ca: a + bi / a - bi
        """
        if self.b >= 0:
            return f"{self.a} + {self.b}i"
        else:
            return f"{self.a} - {-1 * self.b}i"

    def __lt__(self, other):
        """
        Criteriu pentru sortarea descrescatoare in functie de partea imaginara
        """
        return self.b > other.b

    def getModule(self):
        """
        Calculeaza modulul numarului
        """
        return math.sqrt(self.a ** 2 + self.b ** 2)