import matplotlib.pyplot as plt
import math
import sys


f = open ("parameters.txt", "r")

M = int (f.readline ())
M_viz = int (f.readline ())
x = (f.readline ()).split ()
y = (f.readline ()).split ()
grid = (f.readline ()).split ()
value_of_the_math_function_in_the_points_of_grid = (f.readline ()).split ()
L = (f.readline ()).split ()
for i in range (M):
       x[i] = float (x[i])
       y[i] = float (y[i])
for i in range (M_viz):
       grid[i] = float (grid[i])
       value_of_the_math_function_in_the_points_of_grid[i] = float (value_of_the_math_function_in_the_points_of_grid[i])
       L[i] = float (L[i])

f.close ()

fig, ax = plt.subplots ()                                                                                # create plot
ax.plot (grid, value_of_the_math_function_in_the_points_of_grid, "k:", linewidth = 1.0, label = "f(x)")  # draw f(x)
ax.plot (grid, L, "k", linewidth = 1.5, label = "L(x)")                                                  # draw L(x)
ax.plot (x, y, "o")
ax.legend ()                                                                                             # draw legend 

ax.grid ()                                                                                               # draw grid

plt.show ()                                                                                              # show the figure