import matplotlib.pyplot as plt
import csv

x=[] #time
y=[]


with open('data0.csv', 'r') as csvfile:
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(float(row[1]))
        y.append(float(row[0]))


plt.plot(x,y, marker='o')

plt.title('Data from the CSV File ')

plt.xlabel('time')
plt.ylabel('target position')
plt.show()
plt.savefig('A_PLOT.png')

print("hello??")

