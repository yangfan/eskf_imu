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
    fig = plt.figure()

    ax = fig.add_subplot(1, 1, 1, projection="3d")
    ax.plot(data[:, 1], data[:, 2], data[:, 3], linewidth=1)
    ax.set_aspect("equalxy")
    ax.set_title("3D trajectory")

    fig = plt.figure(figsize=(6, 8))
    ax = fig.add_subplot(2, 1, 1)
    ax.plot(data[:, 0], data[:, 4], 'r', linewidth=0.6)
    ax.plot(data[:, 0], data[:, 5], 'g', linewidth=0.6)
    ax.plot(data[:, 0], data[:, 6], 'b', linewidth=0.6)
    ax.plot(data[:, 0], data[:, 7], 'k', linewidth=0.6)
    ax.set_title("Rotation (Qauternion)")
    ax.legend(["qw", "qx", "qy", "qz"])


    ax = fig.add_subplot(2, 1, 2)
    ax.plot(data[:, 0], data[:, 8], 'r')
    ax.plot(data[:, 0], data[:, 9], 'g')
    ax.plot(data[:, 0], data[:, 10], 'b')
    ax.set_title("velocity")
    ax.legend(["vx", "vy", "vz"])

    plt.grid()
    plt.show()
    sys.exit(0)