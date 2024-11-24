import csv
import matplotlib.pyplot as plt

points = []
deviation_method1 = []
deviation_method2 = []

with open('data.txt', 'r', newline='', encoding='utf-8') as file:
    reader = csv.reader(file, delimiter=';')
    next(reader)
    
    for row in reader:
        points.append(int(row[0].strip()))
        deviation_method1.append(float(row[2].strip()))  # Преобразуем Deviation_method1 в float
        deviation_method2.append(float(row[4].strip()))  # Преобразуем Deviation_method2 в float

plt.plot(points, deviation_method1, marker='o', linestyle='-', color='b', label='Deviation Method 1')
plt.plot(points, deviation_method2, marker='s', linestyle='-', color='r', label='Deviation Method 2')

plt.xlabel('Points')
plt.ylabel('Deviation (%)')
plt.title('Зависимость Deviation от Points для двух методов')
plt.legend()
plt.grid(True)
plt.show()
