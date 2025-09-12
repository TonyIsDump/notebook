import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def double_pendulum(t, y, g):
    theta1, omega1, theta2, omega2 = y
    delta = theta2 - theta1
    cdelta = np.cos(delta)
    sdelta = np.sin(delta)
    den = 2 - cdelta**2
    num1 = sdelta * (omega2**2 + omega1**2 * cdelta) + g * (np.sin(theta2) * cdelta - 2 * np.sin(theta1))
    alpha1 = num1 / den
    alpha2 = - omega1**2 * sdelta - g * np.sin(theta2) - cdelta * alpha1
    return np.array([omega1, alpha1, omega2, alpha2])

def rk4_step(f, t, y, dt, g):
    k1 = f(t, y, g)
    k2 = f(t + dt/2, y + dt/2 * k1, g)
    k3 = f(t + dt/2, y + dt/2 * k2, g)
    k4 = f(t + dt, y + dt * k3, g)
    return y + dt/6 * (k1 + 2*k2 + 2*k3 + k4)

# Parameters
g = 9.81
y = np.array([np.pi/3, 2.0, np.pi/8, 4])
dt = 0.001  # Time step
t_end = 100.0
num_steps = int(t_end / dt) + 1
times = np.linspace(0, t_end, num_steps)
solutions = np.zeros((num_steps, 4))
solutions[0] = y

# Integrate
for i in range(1, num_steps):
    y = rk4_step(double_pendulum, times[i-1], y, dt, g)
    solutions[i] = y

# Compute positions (l1 = l2 = 1)
x1 = np.sin(solutions[:, 0])
y1 = -np.cos(solutions[:, 0])
x2 = x1 + np.sin(solutions[:, 2])
y2 = y1 - np.cos(solutions[:, 2])

# Set up the figure and axis
fig, ax = plt.subplots(figsize=(6, 6))
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2)
ax.set_aspect('equal')
ax.grid(True)
line, = ax.plot([], [], 'o-', lw=2, markersize=8)

# Initialization function
def init():
    line.set_data([], [])
    return line,

# Animation function
def animate(i):
    thisx = [0, x1[i], x2[i]]
    thisy = [0, y1[i], y2[i]]
    line.set_data(thisx, thisy)
    return line,

# Create animation (use every 10th frame to speed up display if needed)
ani = FuncAnimation(fig, animate, frames=range(0, num_steps, 15), init_func=init, blit=True, interval=20)

plt.title('Double Pendulum Animation')
plt.show()
