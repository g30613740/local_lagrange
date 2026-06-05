import matplotlib.pyplot as plt

with open ("parameters.txt", "r") as f:
    M = int (f.readline ())
    M_viz = int (f.readline ())
    x = list (map (float, f.readline ().split ()))
    y = list (map (float, f.readline ().split ()))
    grid = list (map (float, f.readline ().split ()))
    f_vals = list (map (float, f.readline ().split ()))
    L_vals = list (map (float, f.readline ().split ()))

plt.style.use ('default')  # style of plot settings

fig, ax = plt.subplots (figsize=(10, 6))

# original f(x) - blue line
ax.plot (grid, f_vals, 'black', linewidth=1.5, label='$f(x) = sin(x)$', alpha=0.8)

# interpolate f(x) - red line
ax.plot (grid, L_vals, 'r-', linewidth=2, label='Локальный полином Лагранжа $L(x)$', alpha=0.9)

# nodes of the interpolation
ax.plot (x, y, 'o', color='green', markersize=1, markeredgecolor='black', 
        markeredgewidth=0.8, label='Узлы интерполяции', zorder=5)

ax.set_title ('Локальная интерполяция многочленами Лагранжа', fontsize=14, fontweight='bold')
ax.set_xlabel ('x', fontsize=12)
ax.set_ylabel ('y', fontsize=12)
ax.legend (loc='upper left', fontsize=10, frameon=True, fancybox=True, shadow=True)
ax.grid (True, linestyle=':', alpha=0.6)
ax.set_xlim (min(grid), max(grid))

plt.savefig ('interpolation_plot.png', dpi=150, bbox_inches='tight')

plt.show ()