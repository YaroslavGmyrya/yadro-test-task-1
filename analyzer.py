import numpy as np
from matplotlib import pyplot as plt
from scipy.special import erfc 

def plot_constellation(constellation, title, labels=True):
    
    if labels == True:
        # iterate on constellation
        for i,point in enumerate(constellation):
            # create labels
            label = bin(i)[2:].zfill(int(np.log2(len(constellation))))
            plt.annotate(label,(point.real, point.imag))

    # plot points
    plt.scatter(constellation.real, constellation.imag)
    plt.grid()
    plt.xlabel("I")
    plt.ylabel("Q")
    plt.title(title)
    plt.show()

# Read files

# for TX constellations testing
QPSK_TX_CONSTELLATION = np.fromfile("pcm/QPSK_constellation.pcm", dtype=np.complex64)
QAM16_TX_CONSTELLATION = np.fromfile("pcm/QAM16_constellation.pcm", dtype=np.complex64)
QAM64_TX_CONSTELLATION = np.fromfile("pcm/QAM64_constellation.pcm", dtype=np.complex64)

# for RX constellations testing
QPSK_RX_CONSTELLATION = np.fromfile("pcm/NOISLY_4_SAMPLES.pcm", dtype=np.complex64)
QAM16_RX_CONSTELLATION = np.fromfile("pcm/NOISLY_16_SAMPLES.pcm", dtype=np.complex64)
QAM64_RX_CONSTELLATION = np.fromfile("pcm/NOISLY_64_SAMPLES.pcm", dtype=np.complex64)

# for BER analysis
QPSK_SNR_AND_BER = np.fromfile("pcm/SNR_BER_QAM_4.pcm", dtype=np.complex64)
QAM16_SNR_AND_BER = np.fromfile("pcm/SNR_BER_QAM_16.pcm", dtype=np.complex64)
QAM64_SNR_AND_BER = np.fromfile("pcm/SNR_BER_QAM_64.pcm", dtype=np.complex64)

# Plot TX constellations
plot_constellation(QPSK_TX_CONSTELLATION, "QPSK constellation on TX")
plot_constellation(QAM16_TX_CONSTELLATION, "QAM16 constellation on TX")
plot_constellation(QAM64_TX_CONSTELLATION, "QAM64 constellation on TX")

# Plot RX constellations
plot_constellation(QPSK_RX_CONSTELLATION, "QPSK constellation on RX, SNR=12", labels=False)
plot_constellation(QAM16_RX_CONSTELLATION, "QAM16 constellation on RX, SNR=12", labels=False)
plot_constellation(QAM64_RX_CONSTELLATION, "QAM64 constellation on RX, SNR=12", labels=False)


# Theoretical BER(SNR)
theoretical_BER_QPSK = 0.5 * erfc(np.sqrt(10 ** (QPSK_SNR_AND_BER.real / 10)))
theoretical_BER_QAM16 = (4/4) * (1 - 1/np.sqrt(16)) * 0.5 * erfc(np.sqrt(3 * 4 * 10 ** (QAM16_SNR_AND_BER.real / 10) / (2 * (16 - 1))))
theoretical_BER_QAM64 = (4/6) * (1 - 1/np.sqrt(64)) * 0.5 * erfc(np.sqrt(3 * 6 * 10 ** (QAM64_SNR_AND_BER.real / 10) / (2 * (64 - 1))))

# Plot BER(SNR)
plt.plot(QPSK_SNR_AND_BER.real, QPSK_SNR_AND_BER.imag, label="Emperical QPSK", marker='*')
plt.plot(QAM16_SNR_AND_BER.real, QAM16_SNR_AND_BER.imag, label="Emperical QAM16", marker='|')
plt.plot(QAM64_SNR_AND_BER.real, QAM64_SNR_AND_BER.imag, label="Emperical QAM64", marker='x')

plt.plot(QPSK_SNR_AND_BER.real, theoretical_BER_QPSK, label="Theoretical QPSK", marker='*')
plt.plot(QAM16_SNR_AND_BER.real, theoretical_BER_QAM16, label="Theoretical QAM16", marker='|')
plt.plot(QAM64_SNR_AND_BER.real, theoretical_BER_QAM64, label="Theoretical QAM64", marker='x')

plt.yscale('log')
plt.ylim(1e-6, 0.5)
plt.grid()
plt.xlabel("E_b/E_n (dB)")
plt.ylabel("BER")
plt.title("BER(SNR)")
plt.legend()
plt.show()
