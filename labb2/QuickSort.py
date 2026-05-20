import matplotlib.pyplot as plt
from collections import defaultdict
import re

# ----------------------------
# Storage: {algorithm: [(N, T, S)]}
# ----------------------------
data = defaultdict(list)

pattern = re.compile(
    r"(\d+)\s+([\d.eE+-]+)\s+([\d.eE+-]+)\s+(\d+)\s+(.*)"
)

# ----------------------------
# Read file (UPDATED NAME)
# ----------------------------
with open("QuickSort.data", "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue

        match = pattern.match(line)
        if not match:
            continue

        N = int(match.group(1))
        T = float(match.group(2))
        S = float(match.group(3))
        typ = match.group(5).strip()

        data[typ].append((N, T, S))

# ----------------------------
# Plot setup
# ----------------------------
plt.figure(figsize=(14, 8))

colors = {
    "QuickSort - Random": "blue",
    "QuickSort MoT - Random": "green",
    "Std::sort - Random": "red"
}

# ----------------------------
# Plot each algorithm
# ----------------------------
for typ, values in data.items():
    values.sort(key=lambda x: x[0])

    Ns = [v[0] for v in values]
    Ts = [v[1] for v in values]
    Ss = [v[2] for v in values]

    avg_stdev = sum(Ss) / len(Ss)

    plt.plot(
        Ns,
        Ts,
        label=f"{typ} (avg σ={avg_stdev:.2f})",
        color=colors.get(typ, None),
        linewidth=2
    )

# ----------------------------
# Styling
# ----------------------------
plt.xlabel("N (input size)")
plt.ylabel("Time (ms)")
plt.title("QuickSort vs QuickSort MoT vs std::sort Performance")

plt.grid(True, alpha=0.3)
plt.legend()

plt.tight_layout()
plt.savefig("quicksort_comparison.png", dpi=300)
plt.show()