import matplotlib.pyplot as plt 
import numpy as np


#Pegando os valores do primeiro arquivo.txt e salvando em valores
with open("resultado", "r") as arquivo:
    valores = arquivo.readlines()

with open ("resultadoOtim", "r") as arquivoOtim:
    valoresOtim = arquivoOtim.readlines()

vetor_tempoGera = []
vetor_tempoCalcula = []
vetor_tempoResiduo = []
vetor_memoryGera = []
vetor_memoryCalcula = []
vetor_memoryResiduo = []
vetor_ratioGera = []
vetor_ratioCalcula = []
vetor_ratioResiduo = []
vetor_energyGera = []
vetor_energyCalcula = []
vetor_energyResiduo = []
vetor_dpGera = []
vetor_avxGera = []
vetor_dpCalcula = []
vetor_avxCalcula = []
vetor_dpResiduo = []
vetor_avxResiduo = []

vetor_tempoGeraotim = []
vetor_tempoCalculaotim = []
vetor_tempoResiduootim = []
vetor_memoryGeraotim = []
vetor_memoryCalculaotim = []
vetor_memoryResiduootim = []
vetor_ratioGeraotim = []
vetor_ratioCalculaotim = []
vetor_ratioResiduootim = []
vetor_energyGeraotim = []
vetor_energyCalculaotim = []
vetor_energyResiduootim = []
vetor_dpGeraotim = []
vetor_avxGeraotim = []
vetor_dpCalculaotim = []
vetor_avxCalculaotim = []
vetor_dpResiduootim = []
vetor_avxResiduootim = []

for i in range(0, 54, 3):
    vetor_tempoGera.append(float(valores[i]))
    vetor_tempoCalcula.append(float(valores[i+1]))
    vetor_tempoResiduo.append(float(valores[i+2]))
    vetor_tempoGeraotim.append(float(valoresOtim[i]))
    vetor_tempoCalculaotim.append(float(valoresOtim[i+1]))
    vetor_tempoResiduootim.append(float(valoresOtim[i+2]))

for i in range(54, 258, 12):
    vetor_dpGera.append(float(valores[i]))
    vetor_avxGera.append(float(valores[i+1]))
    vetor_dpCalcula.append(float(valores[i+2]))
    vetor_avxCalcula.append(float(valores[i+3]))
    vetor_dpResiduo.append(float(valores[i+4]))
    vetor_avxResiduo.append(float(valores[i+5]))
    vetor_dpGeraotim.append(float(valoresOtim[i]))
    vetor_avxGeraotim.append(float(valoresOtim[i+1]))
    vetor_dpCalculaotim.append(float(valoresOtim[i+2]))
    vetor_avxCalculaotim.append(float(valoresOtim[i+3]))
    vetor_dpResiduootim.append(float(valoresOtim[i+4]))
    vetor_avxResiduootim.append(float(valoresOtim[i+5]))
    vetor_memoryGera.append(float(valores[i+6]))
    vetor_memoryCalcula.append(float(valores[i+7]))
    vetor_memoryResiduo.append(float(valores[i+8]))
    vetor_memoryGeraotim.append(float(valoresOtim[i+6]))
    vetor_memoryCalculaotim.append(float(valoresOtim[i+7]))
    vetor_memoryResiduootim.append(float(valoresOtim[i+8]))
    vetor_ratioGera.append(float(valores[i+9]))
    vetor_ratioCalcula.append(float(valores[i+10]))
    vetor_ratioResiduo.append(float(valores[i+11]))
    vetor_ratioGeraotim.append(float(valoresOtim[i+9]))
    vetor_ratioCalculaotim.append(float(valoresOtim[i+10]))
    vetor_ratioResiduootim.append(float(valoresOtim[i+11]))

vetor_dpGera.append(float(valores[258]))
vetor_avxGera.append(float(valores[259]))
vetor_dpCalcula.append(float(valores[260]))
vetor_avxCalcula.append(float(valores[261]))
vetor_dpResiduo.append(float(valores[262]))
vetor_avxResiduo.append(float(valores[263]))
vetor_memoryGera.append(float(valores[264]))
vetor_memoryCalcula.append(float(valores[265]))
vetor_memoryResiduo.append(float(valores[266]))
vetor_ratioGera.append(float(valores[267]))
vetor_ratioCalcula.append(float(valores[268]))
vetor_ratioResiduo.append(float(valores[269]))

vetor_tempoGera = np.log(vetor_tempoGera)
vetor_tempoCalcula = np.log(vetor_tempoCalcula)
vetor_tempoResiduo = np.log(vetor_tempoResiduo)
vetor_tempoGeraotim = np.log(vetor_tempoGeraotim)
vetor_tempoCalculaotim = np.log(vetor_tempoCalculaotim)
vetor_tempoResiduootim = np.log(vetor_tempoResiduootim)




x = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 1000000, 10000000, 100000000]
x = np.log(x)
x2 = [64, 128, 200, 256, 512, 600, 800, 1024, 2000, 3000, 4096, 6000, 7000, 10000, 50000, 1000000, 10000000]
x2 = np.log(x2)


fig, axs = plt.subplots(4, 3, sharex = True)

axs[0, 0].plot(x, vetor_tempoGera, label="semOtim", color="orange")
axs[0, 0].plot(x, vetor_tempoGeraotim, label="comOtim", color="blue")
axs[0, 0].set_ylabel("Tempo (ms)")
axs[0, 0].set_title("Gera")
axs[0, 0].legend()

axs[1, 0].plot(x, vetor_dpGera, label="dpSemOtim", color="orange")
axs[1, 0].plot(x, vetor_avxGera, label="avxSemOtim", color="blue")
axs[1, 0].plot(x2, vetor_dpGeraotim, label="dpComOtim", color="red")
axs[1, 0].plot(x2, vetor_avxGeraotim, label="avxComOtim", color="green")
axs[1, 0].set_xlabel("Número de pontos")
axs[1, 0].set_ylabel("FLOPS_DP e FLOPS_AVX(MFlop/s)")
axs[1, 0].legend()

axs[2, 0].plot(x, vetor_ratioGera, label="semOtim", color="orange")
axs[2, 0].plot(x2, vetor_ratioGeraotim, label="comOtim", color="blue")
axs[2, 0].set_ylabel("Cache miss ratio")
axs[2, 0].legend()

axs[3, 0].plot(x, vetor_memoryGera, label="semOtim", color="orange")
axs[3, 0].plot(x2, vetor_memoryGeraotim, label="comOtim", color="blue")
axs[3, 0].set_ylabel("Memória (MByte/s)")
axs[3, 0].legend()

axs[0, 1].plot(x, vetor_tempoCalcula, label="semOtim", color="orange")
axs[0, 1].plot(x, vetor_tempoCalculaotim, label="comOtim", color="blue")
axs[0, 1].set_ylabel("Tempo (ms)")
axs[0, 1].set_title("Calcula")
axs[0, 1].legend()

axs[1, 1].plot(x, vetor_dpCalcula, label="dpSemOtim", color="orange")
axs[1, 1].plot(x, vetor_avxCalcula, label="avxSemOtim", color="blue")
axs[1, 1].plot(x2, vetor_dpCalculaotim, label="dpComOtim", color="red")
axs[1, 1].plot(x2, vetor_avxCalculaotim, label="avxComOtim", color="green")
axs[1, 1].set_xlabel("Número de pontos")
axs[1, 1].set_ylabel("FLOPS (MFlop/s)")
axs[1, 1].legend()

axs[0, 2].plot(x, vetor_tempoResiduo, label="semOtim", color="orange")
axs[0, 2].plot(x, vetor_tempoResiduootim, label="comOtim", color="blue")
axs[0, 2].set_ylabel("Tempo (ms)")
axs[0, 2].set_title("Residuo")
axs[0, 2].legend()

axs[1, 2].plot(x, vetor_dpResiduo, label="dpSemOtim", color="orange")
axs[1, 2].plot(x, vetor_avxResiduo, label="avxSemOtim", color="blue")
axs[1, 2].plot(x2, vetor_dpResiduootim, label="dpComOtim", color="red")
axs[1, 2].plot(x2, vetor_avxResiduootim, label="avxComOtim", color="green")
axs[1, 2].set_xlabel("Número de pontos")
axs[1, 2].set_ylabel("FLOPS (MFlop/s)")
axs[1, 2].legend()

axs[2, 2].plot(x, vetor_ratioResiduo, label="semOtim", color="orange")
axs[2, 2].plot(x2, vetor_ratioResiduootim, label="comOtim", color="blue")
axs[2, 2].set_ylabel("Cache miss ratio")
axs[2, 2].legend()

axs[3, 2].plot(x, vetor_memoryResiduo, label="semOtim", color="orange")
axs[3, 2].plot(x2, vetor_memoryResiduootim, label="comOtim", color="blue")
axs[3, 2].set_ylabel("Memória (MByte/s)")
axs[3, 2].legend()

plt.show()

