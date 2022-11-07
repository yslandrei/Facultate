from presentation.batchMenu import batchMenu
from presentation.menu import menu


def runUi():
    com = input("Meniul Dorit(n  = Normal, b = Batch): ")
    if com == 'n':
        menu()
    elif com == 'b':
        batchMenu()