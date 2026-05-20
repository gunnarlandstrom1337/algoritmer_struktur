import re
import numpy as np
import matplotlib.pyplot as plt

filename = "../results.data"

# Storage
N_values = []

linear_avg, linear_std = [], []
binary_avg, binary_std = [], []
bst_avg, bst_std = [], []
hash_avg, hash_std = [], []

# Regex
n_pattern = re.compile(r"N\s*=\s*(\d+)")
pattern = re.compile(
    r"(Linear|Binary|BST|Hash) Search Avg:\s*([\d.]+)\s*ns\s*\|\s*StdDev:\s*([\d.]+)\s*ns"
)

# Parse file
with open(filename, "r") as f:
    for line in f:
        line = line.strip()

        # N values
        n_match = n_pattern.match(line)
        if n_match:
            N_values.append(int(n_match.group(1)))
            continue

        # Metrics
        match = pattern.match(line)
        if match:
            algo = match.group(1)
            avg = float(match.group(2))
            std = float(match.group(3))

            if algo == "Linear":
                linear_avg.append(avg)
                linear_std.append(std)
            elif algo == "Binary":
                binary_avg.append(avg)
                binary_std.append(std)
            elif algo == "BST":
                bst_avg.append(avg)
                bst_std.append(std)
            elif algo == "Hash":
                hash_avg.append(avg)
                hash_std.append(std)

# Convert to numpy
N = np.array(N_values)

linear_avg, linear_std = np.array(linear_avg), np.array(linear_std)
binary_avg, binary_std = np.array(binary_avg), np.array(binary_std)
bst_avg, bst_std = np.array(bst_avg), np.array(bst_std)
hash_avg, hash_std = np.array(hash_avg), np.array(hash_std)

# ---- max stddev summary ----
max_std = {
    "Linear": np.max(linear_std),
    "Binary": np.max(binary_std),
    "BST": np.max(bst_std),
    "Hash": np.max(hash_std)
}

# ---- Plot ----
plt.figure(figsize=(12, 7))

plt.plot(N, linear_avg, marker="o", label="Linear Search")
plt.plot(N, binary_avg, marker="s", label="Binary Search")
plt.plot(N, bst_avg, marker="^", label="BST Search")
plt.plot(N, hash_avg, marker="d", label="Hash Search")

plt.xscale("linear")
plt.xlim(0, 200000)

plt.xlabel("N (Input Size)")
plt.ylabel("Average Time (ns)")
plt.title("Search Algorithm Performance Comparison")

plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend()

# ---- Summary box ----
summary_text = (
    f"Max StdDev:\n"
    f"Linear: {max_std['Linear']:.2f} ns\n"
    f"Binary: {max_std['Binary']:.2f} ns\n"
    f"BST: {max_std['BST']:.2f} ns\n"
    f"Hash: {max_std['Hash']:.2f} ns"
)

plt.gca().text(
    0.02, 0.98,
    summary_text,
    transform=plt.gca().transAxes,
    fontsize=10,
    verticalalignment="top",
    bbox=dict(boxstyle="round", facecolor="white", alpha=0.85)
)

plt.tight_layout()
plt.show()