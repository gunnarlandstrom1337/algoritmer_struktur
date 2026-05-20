import matplotlib.pyplot as plt
from collections import defaultdict

data = defaultdict(list)
max_points = {}  # typ -> (N, T, S)

# ---- Read file ----
with open("SelectionSort.data", "r") as f:
    for line in f:
        if not line.strip():
            continue

        parts = line.split()

        try:
            N = int(parts[0])
            T = float(parts[1])
            S = float(parts[2])
            typ = " ".join(parts[3:]).strip()

            data[typ].append((N, T, S))

            if typ not in max_points or S > max_points[typ][2]:
                max_points[typ] = (N, T, S)

        except (ValueError, IndexError):
            continue

# ---- Plot ----
fig, ax = plt.subplots(figsize=(12, 7))

for typ, values in data.items():
    values.sort(key=lambda x: x[0])

    N_vals = [v[0] for v in values]
    T_vals = [v[1] for v in values]

    max_N, max_T, max_S = max_points[typ]

    line, = ax.plot(
        N_vals,
        T_vals,
        label=f"{typ} (max σ = {max_S:.3f})"
    )

    color = line.get_color()

    # only mark the max point (no horizontal lines)
    ax.scatter(max_N, max_T, color=color, s=80, zorder=5)

# ---- Styling ----
ax.set_xlabel("N (Number of elements)")
ax.set_ylabel("Time (ms)")
ax.set_title("Selection Sort Performance")
ax.legend(title="Dataset Type")
ax.grid(True)

plt.tight_layout()
plt.savefig("selection_sort_time.png", dpi=300)
plt.show()