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
    #plot 1: OVERALL
    plt.subplot(1, 3, 1)
    plt.plot(time, s_pos, label="sender")
    plt.plot(time, r_pos, label="receiver")
    plt.plot(time, target, linestyle='dashed', label="target")
    plt.axhspan(0.0, 0.3, color='tab:blue', alpha=0.1)
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Position')
    plt.ylim(-1.5, 2)

    #plot 2: RECEIVER
    plt.subplot(1, 3, 2)
    plt.plot(time, r_pos, label="position sensor", color="tab:orange")
    plt.plot(time, r_contact, label="contact sensor", color="rebeccapurple")
    plt.plot(time, r_target, label="target sensor (constant value)", color="maroon")
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Receiver\'s Sensor Value')
    plt.ylim(-1.5, 2)

    #plot 3: SENDER
    plt.subplot(1, 3, 3)
    plt.plot(time, s_pos, label="position sensor")
    plt.plot(time, s_contact, label="contact sensor", color="rebeccapurple")
    plt.plot(time, s_target, label="target sensor", color="maroon")
    plt.axhspan(0.0, 0.3, color='tab:blue', alpha=0.1)
    plt.legend()
    plt.xlabel('Time')
    plt.ylabel('Sender\'s Sensor Value')
    plt.ylim(-1.5, 2)

    plt.tight_layout()
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

    plt.figure()
    plt.plot(gen, mean_fit, marker='o')

    plt.title('Mean Fitness vs Generations')
    plt.xlabel('Generations')
    plt.ylabel('Mean Fitness')
    # plt.show()
    plt.savefig('plots/MeanFitVsGen.png')

    # fig1, ax1 = plt.subplots()
    # ax1.set_title('Basic Plot')
    # ax1.boxplot(mean_fit)
    # # ax1.boxplot(r_pos)
    # fig1.savefig('plots/mean_box_plot.png')

# BestFitVsGeneration
def bestFitvsGenerations():
    gen=[]
    best_fit=[]
    
    with open('data/BestFitVsGeneration.csv', 'r') as csvfile:
        csvfile = open('data/BestFitVsGeneration.csv', 'r') 
        plots= csv.reader(csvfile, delimiter=',')
        for row in plots:
            gen.append(float(row[0]))
            best_fit.append(float(row[1]))

    plt.figure()
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
    plt.grid()

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
    plt.plot(target, target, marker='o', label='Perfect fitness', color='tab:orange')
    plt.plot(target, mean_pos, marker='o', label='Average fitness', color='tab:blue')
    plt.grid()
    plt.legend()

    plt.title('Mean Final Position vs Target position')
    plt.xlabel('Target Position')
    plt.ylabel('Mean final position')
    plt.savefig('plots/MeanFinalPos.png')


def plotContactTime():
    target=[]
    mean_contact_time=[]
    
    csvfile = open('data/MeanContactTime.csv', 'r') 
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        target.append(float(row[0]))
        mean_contact_time.append(float(row[1]))

    plt.figure()
    plt.plot(target, mean_contact_time, marker='o')
    plt.grid()

    plt.title('Mean Contact Time vs Target position')
    plt.xlabel('Target Position')
    plt.ylabel('Mean contact time')
    plt.savefig('plots/MeanContactTime.png')


# target/final position Vs generation
def perfectSolution():
    gen=[]
    target=[]
    final_pos=[]
    
    csvfile = open('data/TargetFinalPos.csv', 'r') 
    plots= csv.reader(csvfile, delimiter=',')
    for row in plots:
        gen.append(float(row[0]))
        target.append(float(row[1]))
        final_pos.append(float(row[2]))

    print(len(target))

    plt.figure()
    plt.plot(gen, final_pos)
    plt.plot(gen, target)

    plt.title('target/final position Vs generation')
    plt.xlabel('Generation')
    plt.ylabel('Position')
    plt.savefig('plots/FinalPosVsGeneration.png')


def main():
    # call the plotter functions here
    meanFitvsGenerations()
    bestFitvsGenerations()
    plotDiachronic()
    absMeanDistance()
    plotMeanFinalPosition()
    plotContactTime()
    # perfectSolution()

    print("Plots have been plotted. :) ")


if __name__ == "__main__":
    main()
