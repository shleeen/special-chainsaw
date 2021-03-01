import matplotlib.pyplot as plt
import csv

def meanFitvsGenerations():
    gen=[]
    mean_fit=[]
    
    with open('MeanFitness.csv', 'r') as csvfile:
        csvfile = open('MeanFitness.csv', 'r') 
        plots= csv.reader(csvfile, delimiter=',')
        for row in plots:
            gen.append(float(row[0]))
            mean_fit.append(float(row[1]))

    f1 = plt.figure()
    plt.plot(gen, mean_fit, marker='o')

    plt.title('Mean Fitness vs Generations')
    plt.xlabel('Generations')
    plt.ylabel('Mean Fitness')
    # plt.show()
    plt.savefig('MeanFitVsGen.png')


def bestFitvsGenerations():
    gen=[]
    best_fit=[]
    
    with open('FitnessVsGeneration.csv', 'r') as csvfile:
        csvfile = open('FitnessVsGeneration.csv', 'r') 
        plots= csv.reader(csvfile, delimiter=',')
        for row in plots:
            gen.append(float(row[0]))
            best_fit.append(float(row[1]))

    plt.figure(0)
    plt.plot(gen, best_fit) #, marker='x'

    plt.title('Best Fitness vs Generations')
    plt.xlabel('Generations')
    plt.ylabel('Best Fitness')
    plt.savefig('BestFitVsGen.png')


def main():
    # call the plotter functions here
    bestFitvsGenerations()
    meanFitvsGenerations()

    print("something has been plotted. :) ")


if __name__ == "__main__":
    main()
