import numpy as np
from matplotlib import pyplot as plt

def plot_constellation(constellation, title):
    for i,point in enumerate(constellation):
        label = bin(i)[2:].zfill(int(np.log2(len(constellation))))
        plt.annotate(
            label,
            (point.real, point.imag),
            textcoords="offset points",
        )

    plt.scatter(constellation.real, constellation.imag)
    plt.grid()
    plt.xlabel("I")
    plt.ylabel("Q")
    plt.title(title)
    plt.show()

qpsk_constellation = np.fromfile("../pcm/qpsk_constellation.pcm", dtype=np.complex64)
qam16_constellation = np.fromfile("../pcm/qam16_constellation.pcm", dtype=np.complex64)
qam64_constellation = np.fromfile("../pcm/qam64_constellation.pcm", dtype=np.complex64)

plot_constellation(qpsk_constellation, "QPSK constellation")
plot_constellation(qam16_constellation, "QAM16 constellation")
plot_constellation(qam64_constellation, "QAM64 constellation")
