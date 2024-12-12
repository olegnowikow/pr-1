import calendar 
from datetime import datetime

def print_calendar(year, month):
    """ 
    Выводит календарь для заданного года и месяца.
    """
    print(calendar.month(year, month))

def main():

    print("простой календарь")
    while True:
        try:
            year = input("Введите год (или 'exit' для выхода): ")
            if year.lower() == 'exit':
                break
            year = int(year)
            month = int(input("Введите месяц (1-12): "))
            if month < 1 or month > 12:    
                print("Некорректный месяц. Попробуйте снова.")
                continue
            print_calendar (year, month)
        except ValueError:
            print("Введите целое число. Попробуйте снова.")

if __name__ == "__main__":
    main()