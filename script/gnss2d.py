#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Please provide path of the data.")
        sys.exit(1)
    path = sys.argv[1]
    data = np.loadtxt(path)
    # plt.plot(data[:, 1], data[:, 2], linewidth=0.5)
    plt.scatter(data[:, 1], data[:, 2], s=0.5)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("2D GPS trajectory")
    # plt.grid()
    plt.gca().set_aspect('equal')
    plt.show()
    sys.exit(0)