import re
import numpy as np
import matplotlib.pyplot as plt

filename = "../resultsNoLinear.data"

# Data storage
N_values = []

binary_avg, binary_std = [], []
bst_avg, bst_std = [], []
hash_avg, hash_std = [], []

# Regex
n_pattern = re.compile(r"N\s*=\s*(\d+)")
pattern = re.compile(
    r"(Binary|BST|Hash) Search Avg:\s*([\d.]+)\s*ns\s*\|\s*StdDev:\s*([\d.]+)\s*ns"
)

# Parse file
with open(filename, "r") as f:
    for line in f:
        line = line.strip()

        n_match = n_pattern.match(line)
        if n_match:
            N_values.append(int(n_match.group(1)))
            continue

        match = pattern.match(line)
        if match:
            t = match.group(1)
            avg = float(match.group(2))
            std = float(match.group(3))

            if t == "Binary":
                binary_avg.append(avg)
                binary_std.append(std)
            elif t == "BST":
                bst_avg.append(avg)
                bst_std.append(std)
            elif t == "Hash":
                hash_avg.append(avg)
                hash_std.append(std)

# Convert
N = np.array(N_values)

binary_avg, binary_std = np.array(binary_avg), np.array(binary_std)
bst_avg, bst_std = np.array(bst_avg), np.array(bst_std)
hash_avg, hash_std = np.array(hash_avg), np.array(hash_std)

# ---- Compute max stddev per algorithm ----
max_std = {
    "Binary": np.max(binary_std),
    "BST": np.max(bst_std),
    "Hash": np.max(hash_std)
}

# ---- Plot ----
plt.figure(figsize=(12, 7))

plt.plot(N, binary_avg, marker="o", label="Binary Search")
plt.plot(N, bst_avg, marker="s", label="BST Search")
plt.plot(N, hash_avg, marker="d", label="Hash Search")

plt.xscale("linear")
plt.xlim(0, 200000)

plt.xlabel("N (Input Size)")
plt.ylabel("Average Time (ns)")
plt.title("Search Algorithm Performance")

plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend()

# ---- Summary box ----
summary_text = (
    f"Max StdDev:\n"
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
    bbox=dict(boxstyle="round", facecolor="white", alpha=0.8)
)

plt.tight_layout()
plt.show()