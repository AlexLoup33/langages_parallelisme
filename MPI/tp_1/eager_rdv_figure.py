import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load measurements
df = pd.read_csv("eager_rendez-vous_latence.txt")

# The current MPI benchmark sends `i` integers.
# Convert the number of integers to bytes.
df["message_size_bytes"] = df["message_size"] * 4

# Convert seconds to microseconds
df["latency_us"] = df["time_seconds"] * 1e6

# Sort measurements by message size
df = df.sort_values("message_size_bytes")

# Create figure
fig, ax = plt.subplots(figsize=(10, 6))

ax.scatter(
    df["message_size_bytes"],
    df["latency_us"],
    s=35,
    alpha=0.8
)

ax.set_xscale("log", base=2)
ax.set_xlabel("Message size (bytes)")
ax.set_ylabel("MPI_Send duration (µs)")
ax.set_title("MPI_Send Latency vs. Message Size")

ax.grid(True, which="both", linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("mpi_send_latency.png", dpi=300, bbox_inches="tight")
plt.show()