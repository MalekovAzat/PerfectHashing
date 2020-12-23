import matplotlib.pyplot as plt


def main():
    exp1()
    exp2()
    exp3()


def exp1():
    fileName = 'build/exp1.txt'
    f = open(fileName)
    compressionCoeffs = []
    creatingTimes = []
    sizeOfSubtables = []

    for line in f:
        line = line.split(',')
        compressionCoeffs.append(float(line[0]))
        creatingTimes.append(int(line[1]))
        sizeOfSubtables.append(int(line[2]))
    fig, ax = plt.subplots()
    ax.plot(compressionCoeffs, creatingTimes)
    plt.title("Dependency between compression and preprocessing time")
    plt.xlabel("Compressions")
    plt.ylabel("Preprocessing time ms")
    fig.savefig('PreprTime.png')
    fig, ax = plt.subplots()
    ax.plot(compressionCoeffs, sizeOfSubtables)
    plt.title("Dependency between compression and subtable sizes time", pad="20")
    plt.xlabel("Compressions")
    plt.ylabel("Subtables size ")
    fig.savefig('PreprSize.png')


def exp2():
    fileName = 'build/exp2.txt'
    f = open(fileName)
    sizeOfTables = []
    preprTimePerf = []
    preprTimeSquare = []

    for line in f:
        line = line.split(',')
        sizeOfTables.append(float(line[0]))
        preprTimePerf.append(int(line[1]))
        preprTimeSquare.append(int(line[2]))

    fig, ax = plt.subplots()
    ax.plot(sizeOfTables, preprTimePerf, label="PerfectHashT")
    ax.plot(sizeOfTables, preprTimeSquare, label="SquareHashT")
    plt.title(
        "Dependency between count of inserting elements and preprocessing time")
    plt.xlabel("Inserting elements")
    plt.ylabel("Preprcessing time microseconds")
    plt.legend()
    fig.savefig('PreprocessingDifference.png')


def exp3():
    fileName = 'build/exp3.txt'

    f = open(fileName)
    sizeOfTables = []
    searchTimePerf = []
    searchTimeSquare = []

    for line in f:
        line = line.split(',')
        sizeOfTables.append(float(line[0]))
        searchTimePerf.append(int(line[1]))
        searchTimeSquare.append(int(line[2]))

    fig, ax = plt.subplots()
    plt.title(
        "Dependency between count of searching elements and preprocessing time")
    ax.plot(sizeOfTables, searchTimePerf, label="PerfectHashT")
    ax.plot(sizeOfTables, searchTimeSquare, label="SquareHashT")
    plt.xlabel("searching elements")
    plt.ylabel("searching time in microseconds")
    plt.legend()
    fig.savefig('SearchingDifference.png')


if __name__ == "__main__":
    main()
