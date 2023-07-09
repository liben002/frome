import os
import sys
import cv2
import math
import numpy as np


def main():
    if len(sys.argv) != 2:
        print("Usage: `./main.py [path to directory]")
        exit(1)
    elif not os.path.exists(sys.argv[1]):
        print("Directory is invalid")
        exit(2)

    frames = os.listdir(sys.argv[1])
    frames.sort()
    hline = []

    # https://note.nkmk.me/en/python-opencv-imread-imwrite/
    for frame in frames:
        p = os.path.join(sys.argv[1], frame)
        im = cv2.imread(p)

        num_pixels = len(im) * len(im[0])
        red = math.floor(np.sum(im[:, :, 2]) / num_pixels)
        blue = math.floor(np.sum(im[:, :, 0]) / num_pixels)
        green = math.floor(np.sum(im[:, :, 1]) / num_pixels)
        hline.append([blue, green, red])

    frome = []
    for i in range(math.floor(len(hline) * 9/16)):
        frome.append(hline)
    print([hline])

    cv2.imwrite("frome.png", np.array(frome))


if __name__ == "__main__":
    main()
