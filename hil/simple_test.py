#!/usr/bin/env python3
import subprocess
import time

print("Starting simple HIL test...")

# Start the simulator
proc = subprocess.Popen(
    ["./build/sensor_sim"],
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE,
    text=True
)

# Wait a moment
time.sleep(0.5)

# Send a command
print("Sending HELP command...")
proc.stdin.write("HELP\n")
proc.stdin.flush()

# Read response (with timeout)
time.sleep(0.2)
for i in range(5):
    line = proc.stdout.readline()
    print(f"Got: {line.strip()}")
    if "Commands" in line:
        print("✓ Test passed!")
        break

# Cleanup
proc.terminate()
proc.wait()
