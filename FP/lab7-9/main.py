from ui.menu import menu
from tests.runAllTests import runAllTests


def main():
    runAllTests()
    Menu = menu()
    Menu.runMenu()

if __name__ == "__main__":
    main()