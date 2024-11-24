import csv
import matplotlib.pyplot as plt

points = []
area_method1 = []
area_method2 = []

with open('data.txt', 'r', newline='', encoding='utf-8') as file:
    reader = csv.reader(file, delimiter=';')
    
    next(reader)
    
    for row in reader:
        points.append(int(row[0].strip()))
        area_method1.append(float(row[1].strip()))  # Преобразуем Area_method1 в float
        area_method2.append(float(row[3].strip()))  # Преобразуем Area_method2 в float

plt.plot(points, area_method1, marker='o', linestyle='-', color='b', label='Area Method 1')
plt.plot(points, area_method2, marker='s', linestyle='-', color='r', label='Area Method 2')

plt.xlabel('Points')
plt.ylabel('Area')
plt.title('Зависимость Area от Points для двух методов')
plt.legend()
plt.grid(True) 
plt.show()
