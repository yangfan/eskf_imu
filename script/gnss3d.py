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
    ax = plt.axes(projection='3d')
    # ax.scatter(data[:, 1], data[:, 2], data[:, 3], c="red", marker='o', s=0.5)
    # ax.plot(data[:, 1], data[:, 2], data[:, 3], c="red", marker='o', s=0.5)
    ax.plot(data[:, 1], data[:, 2], data[:, 3],  linewidth=0.5)
    ax.set_aspect("equalxy")

    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.set_zlim(-5, 5)
    plt.title("3D GPS trajectory")
    plt.grid()
    plt.show()

    sys.exit(0)