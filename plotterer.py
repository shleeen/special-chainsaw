import matplotlib.pyplot as plt
import csv

def fig8():
    s_pos=[]
    r_pos=[]
    time=[]
    target=[]
    
    with open('data/Fig8_yes.csv', 'r') as csvfile:
        csvfile = open('data/Fig8_yes.csv', 'r') 
        plots= csv.reader(csvfile, delimiter=',')
        for row in plots:
            time.append(float(row[0]))
            target.append(float(row[1]))
            s_pos.append(float(row[2]))
            r_pos.append(float(row[3]))

    f2 = plt.figure()
    plt.plot(time, s_pos)
    plt.plot(time, r_pos)
    # plt.plot(time, target, linestyle='dashed')

    plt.title('Target = 0.8')
    plt.xlabel('Time')
    plt.ylabel('Position')
    # plt.show()
    plt.savefig('plots/Fig8.png')


def meanFitvsGenerations():
    gen=[]
    mean_fit=[]
    
    with open('data/MeanFitness.csv', 'r') as csvfile:
        csvfile = open('data/MeanFitness.csv', 'r') 
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
    plt.savefig('plots/MeanFitVsGen.png')


def bestFitvsGenerations():
    gen=[]
    best_fit=[]
    
    with open('data/FitnessVsGeneration.csv', 'r') as csvfile:
        csvfile = open('data/FitnessVsGeneration.csv', 'r') 
        plots= csv.reader(csvfile, delimiter=',')
        for row in plots:
            gen.append(float(row[0]))
            best_fit.append(float(row[1]))

    plt.figure(0)
    plt.plot(gen, best_fit) #, marker='x'

    plt.title('Best Fitness vs Generations')
    plt.xlabel('Generations')
    plt.ylabel('Best Fitness')
    plt.savefig('plots/BestFitVsGen.png')


def main():
    # call the plotter functions here
    bestFitvsGenerations()
    meanFitvsGenerations()
    fig8()

    print("something has been plotted. :) ")


if __name__ == "__main__":
    main()
