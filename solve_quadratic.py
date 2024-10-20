import math

def solve_quadratic(a, b, c):
    if a == 0:
        if b == 0:
            print(f"Это не уравнение, так как a и b равны нулю.")
            return 0
        else:
            print(f"Это линейное уравнение. Корень: {-c / b}")
            return 0
    discriminant = b**2 - 4*a*c
    if discriminant < 0:
        print("Нет корней")
    elif discriminant == 0:
        root = -b / (2 * a)
        print(f"Один корень: {root}")
    else:
        root1 = (-b + math.sqrt(discriminant)) / (2 * a)
        root2 = (-b - math.sqrt(discriminant)) / (2 * a)
        print(f"Два корня: {root1} и {root2}")

if __name__ == "__main__":
    print("Решатель квадратного уравнения вида ax^2+bx+c=0.")
    a = float(input("Введите коэффициент а: "))
    b = float(input("Введите коэффициент b: "))
    c = float(input("Введите коэффициент с: "))
    solve_quadratic(a, b, c)