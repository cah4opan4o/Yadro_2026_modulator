import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.special import erfc

def theoretical_ber_qpsk(snr_db):
    snr = 10**(snr_db / 10)
    return 0.5 * erfc(np.sqrt(snr))

def theoretical_ber_qam(snr_db, M):
    snr = 10**(snr_db / 10)
    k = np.log2(M)
    return (2/k) * (1 - 1/np.sqrt(M)) * erfc(np.sqrt(3*k*snr / (2*(M-1))))

def plot_ber():
    try:
        df = pd.read_csv('build/results.csv') 
    except FileNotFoundError:
        print("Файл results.csv не найден!")
        return

    plt.figure(figsize=(12, 8))
    snr_axis = df.columns[1:].astype(float)
    # Генерируем плавную кривую для теории
    theory_snr = np.linspace(snr_axis.min(), snr_axis.max(), 100)

    # Цвета для графиков, чтобы симуляция и теория одного типа модуляции совпадали
    colors = ['blue', 'red', 'green']
    mod_names = ["QPSK", "QAM16", "QAM64"]

    # --- 1. Отрисовка экспериментальных данных (Соединенные точки) ---
    for i, (index, row) in enumerate(df.iterrows()):
        label = f"Sim: {row.iloc[0]}"
        # '-o' означает сплошную линию с круглыми маркерами
        plt.semilogy(snr_axis, row.iloc[1:].astype(float), '-o', 
                     label=label, color=colors[i], linewidth=1.5, markersize=5)

    # --- 2. Отрисовка теории (Пунктирные линии) ---
    plt.semilogy(theory_snr, theoretical_ber_qpsk(theory_snr), 
                 '--', color=colors[0], alpha=0.6, label='Theory: QPSK')
    
    plt.semilogy(theory_snr, theoretical_ber_qam(theory_snr, 16), 
                 '--', color=colors[1], alpha=0.6, label='Theory: QAM16')
    
    plt.semilogy(theory_snr, theoretical_ber_qam(theory_snr, 64), 
                 '--', color=colors[2], alpha=0.6, label='Theory: QAM64')

    # Оформление графика
    plt.grid(True, which="both", ls="-", alpha=0.3)
    plt.xlabel('SNR (Eb/No) (dB)', fontsize=12)
    plt.ylabel('Bit Error Rate (BER)', fontsize=12)
    plt.title('Сравнение симуляции и теоретического BER (Gray Code)', fontsize=14)
    plt.legend()
    plt.ylim(1e-6, 1)
    
    plt.savefig('ber_plot.png')
    print("График сохранен в файл ber_plot.png")
    plt.show()

if __name__ == "__main__":
    plot_ber()
