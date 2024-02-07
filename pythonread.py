import numpy as np
import matplotlib.pyplot as plt
t, x, y, z = np.loadtxt('sir_output.txt', skiprows=1, unpack=True)

plt.plot(x, label='Susceptible')
plt.plot(y, label='Infected')
plt.plot(z, label='Recovered')
plt.xlabel('Days')
plt.ylabel('Population')
plt.title('SIR Model')
plt.legend()

plt.show()

print(t)
print(x)
print(y)
print(z)