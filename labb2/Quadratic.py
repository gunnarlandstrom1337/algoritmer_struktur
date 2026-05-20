import matplotlib.pyplot as plt
from collections import defaultdict
import re

# ----------------------------
# Storage
# ----------------------------
data = defaultdict(list)

pattern = re.compile(
    r"(\d+)\s+([\d.eE+-]+)\s+([\d.eE+-]+)\s+(\d+)\s+(.*)"
)

# ----------------------------
# Read file
# ----------------------------
with open("Quadratic.data", "r", encoding="utf-8") as f:
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

# Auto color palette (so you don’t need to hardcode)
colors = plt.cm.tab10.colors

# ----------------------------
# Plot each algorithm
# ----------------------------
for idx, (typ, values) in enumerate(sorted(data.items())):
    values.sort(key=lambda x: x[0])

    Ns = [v[0] for v in values]
    Ts = [v[1] for v in values]
    Ss = [v[2] for v in values]

    color = colors[idx % len(colors)]

    # ----------------------------
    # Time curve
    # ----------------------------
    plt.plot(
        Ns,
        Ts,
        label=typ,
        color=color,
        linewidth=2
    )

    # ----------------------------
    # Stats
    # ----------------------------
    avg_stdev = sum(Ss) / len(Ss)
    top3 = sorted(zip(Ns, Ts, Ss), key=lambda x: x[2], reverse=True)[:3]

    # ----------------------------
    # Highlight top 3 σ points
    # ----------------------------
    for (n, t, s) in top3:
        plt.scatter(
            n,
            t,
            color=color,
            s=90,
            edgecolors="black",
            zorder=5
        )

    # ----------------------------
    # Stats text
    # ----------------------------
    stats_text = f"{typ}\navg σ = {avg_stdev:.3f}\n"
    for i, (n, t, s) in enumerate(top3, start=1):
        stats_text += f"#{i}: σ={s:.3f} (N={n})\n"

    # Spread boxes vertically automatically
    plt.text(
        0.02,
        0.95 - idx * 0.12,
        stats_text,
        transform=plt.gca().transAxes,
        fontsize=8,
        color=color,
        verticalalignment="top",
        bbox=dict(facecolor="white", alpha=0.75, edgecolor=color)
    )

# ----------------------------
# Styling
# ----------------------------
plt.xlabel("N (input size)")
plt.ylabel("Time (ms)")
plt.title("Sorting Algorithm Performance Comparison")

plt.grid(True, alpha=0.3)
plt.legend(fontsize=8)

plt.tight_layout()
plt.savefig("sorting_comparison.png", dpi=300)
plt.show()