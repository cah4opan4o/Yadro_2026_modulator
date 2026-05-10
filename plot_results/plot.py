import pandas as pd
import matplotlib.pyplot as plt

def plot_ber():
    try:
        df = pd.read_csv('build/results.csv') 

    except FileNotFoundError:
        print("Файл results.csv не найден!")
        return

    plt.figure(figsize=(10, 7))

    snr = df.columns[1:].astype(float)
    
    for index, row in df.iterrows():
        label = row.iloc[0] 
        
        ber = row.iloc[1:].astype(float)
        
        plt.semilogy(snr, ber, marker='o', label=label, linewidth=2)

    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.xlabel('SNR (Eb/N0), dB', fontsize=12)
    plt.ylabel('Bit Error Rate (BER)', fontsize=12)
    plt.title('Сравнение эффективности модуляций (QPSK, QAM16, QAM64)', fontsize=14)
    plt.legend()
    
    plt.ylim(1e-5, 1)
    
    plt.savefig('ber_plot.png')
    print("График сохранен в файл ber_plot.png")
    plt.show()

if __name__ == "__main__":
    plot_ber()
