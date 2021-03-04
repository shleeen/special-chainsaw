import matplotlib.pyplot as plt
import csv

def plotDiachronic():
    plt.rcParams["figure.figsize"] = (15, 5)
    # plt.xlim(-5, 5)
    plt.ylim(-1, 2)

    time=[]
    target=[]
    s_pos=[]
    r_pos=[]
    s_contact=[]
    r_contact=[]
    s_target=[]
    r_target=[]

    csvfile = open('data/diachronic.csv', 'r') 
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        time.append(float(row[0]))
        target.append(float(row[1]))
        s_pos.append(float(row[2]))
        r_pos.append(float(row[3]))
        s_contact.append(float(row[4]))
        r_contact.append(float(row[5]))
        s_target.append(float(row[6]))
        r_target.append(float(row[7]))

    f1 = plt.figure()
    plt.suptitle('Target = 0.8 ')
    #plot 1:
    plt.subplot(1, 3, 1)
    plt.plot(time, s_pos, label="sender")
    plt.plot(time, r_pos, label="receiver")
    plt.plot(time, target, linestyle='dashed', label="target")
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Position')
    # plt.ylim(-1, 2)

    #plot 2:
    plt.subplot(1, 3, 2)
    plt.plot(time, r_contact, label="contact sensor")
    plt.plot(time, r_pos, label="position sensor")
    plt.plot(time, r_target, label="target sensor (constant value)")
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Receiver\'s Sensor Value')
    # plt.ylim(-1, 2)

    #plot 3:
    plt.subplot(1, 3, 3)
    plt.plot(time, s_contact, label="contact sensor")
    plt.plot(time, s_pos, label="position sensor")
    plt.plot(time, s_target, label="target sensor (constant value)")
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Sender\'s Sensor Value')
    # plt.ylim(-1, 2)

    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
    # plt.show()

    plt.savefig('plots/diachronic_plots.png')



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

    fig1, ax1 = plt.subplots()
    ax1.set_title('Basic Plot')
    ax1.boxplot(mean_fit)
    # ax1.boxplot(r_pos)
    fig1.savefig('plots/mean_box_plot.png')


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


def absMeanDistance():
    target=[]
    mean_dist=[]
    
    csvfile = open('data/AbsMeanDist.csv', 'r') 
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        target.append(float(row[0]))
        mean_dist.append(float(row[1]))

    plt.figure()
    plt.plot(target, mean_dist, marker='o')

    plt.title('Absolute mean distance vs Target position')
    plt.xlabel('Target Position')
    plt.ylabel('Absolute mean distance to target')
    plt.savefig('plots/AbsMeanDist.png')


def plotMeanFinalPosition():
    target=[]
    mean_pos=[]
    
    csvfile = open('data/MeanFinalPosition.csv', 'r') 
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        target.append(float(row[0]))
        mean_pos.append(float(row[1]))

    plt.figure()
    plt.plot(target, mean_pos, marker='o')

    plt.title('Mean Final Position vs Target position')
    plt.xlabel('Target Position')
    plt.ylabel('Mean final position')
    plt.savefig('plots/MeanFinalPos.png')


def main():
    # call the plotter functions here
    bestFitvsGenerations()
    meanFitvsGenerations()
    plotDiachronic()
    absMeanDistance()
    plotMeanFinalPosition()

    print("something has been plotted. :) ")


if __name__ == "__main__":
    main()
