#!/usr/bin/env python3
import subprocess
import time
import sys

class SimulatedDevice:
    def __init__(self, executable="./build/sensor_sim"):
        self.proc = subprocess.Popen(
            [executable],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1
        )
        time.sleep(0.2)
        # Drain the banner lines
        self._drain_output(0.3)
    
    def _drain_output(self, timeout=0.1):
        """Drain any pending output"""
        start = time.time()
        while time.time() - start < timeout:
            try:
                line = self.proc.stdout.readline()
                if not line:
                    break
            except:
                break
    
    def send(self, cmd):
        self.proc.stdin.write(f"{cmd}\n")
        self.proc.stdin.flush()
        time.sleep(0.05)  # Give time to process
    
    def receive(self, timeout=1.0):
        start = time.time()
        while time.time() - start < timeout:
            line = self.proc.stdout.readline().strip()
            if line:
                return line
            time.sleep(0.01)
        return ""
    
    def close(self):
        try:
            self.proc.terminate()
            self.proc.wait(timeout=2)
        except:
            self.proc.kill()

class HILTestRunner:
    def __init__(self, device):
        self.device = device
        self.passed = 0
        self.failed = 0
    
    def test_help(self):
        print("Testing HELP command...", end=" ")
        self.device.send("HELP")
        response = self.device.receive()
        if "Commands" in response:
            print("✓ PASS")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def test_calibrate(self):
        print("Testing CALIBRATE command...", end=" ")
        self.device.send("CALIBRATE")
        response = self.device.receive()
        if "OK" in response and "Calibrated" in response:
            print("✓ PASS")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def test_status(self):
        print("Testing STATUS command...", end=" ")
        self.device.send("STATUS")
        response = self.device.receive()
        if "Healthy" in response or "OK" in response:
            print("✓ PASS")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def test_read(self):
        print("Testing READ command...", end=" ")
        self.device.send("READ")
        response = self.device.receive()
        if "TEMP:" in response and "HUM:" in response:
            print(f"✓ PASS - {response}")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def test_offset(self):
        print("Testing OFFSET command...", end=" ")
        self.device.send("OFFSET 5 10")
        response = self.device.receive()
        if "OK" in response and "Offset" in response:
            print("✓ PASS")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def test_invalid(self):
        print("Testing invalid command...", end=" ")
        self.device.send("INVALID_CMD")
        response = self.device.receive()
        if "ERROR" in response or "Unknown" in response:
            print("✓ PASS")
            self.passed += 1
            return True
        else:
            print(f"✗ FAIL - Got: '{response}'")
            self.failed += 1
            return False
    
    def run_all_tests(self):
        print("\n" + "="*60)
        print("Starting HIL Tests")
        print("="*60 + "\n")
        
        self.test_help()
        self.test_calibrate()
        self.test_status()
        self.test_read()
        self.test_offset()
        self.test_read()  # Read again with offset
        self.test_invalid()
        
        print("\n" + "="*60)
        print(f"Results: {self.passed} passed, {self.failed} failed")
        print("="*60 + "\n")
        
        return self.failed == 0

def main():
    print("Using simulated device")
    device = SimulatedDevice()
    
    try:
        runner = HILTestRunner(device)
        success = runner.run_all_tests()
        sys.exit(0 if success else 1)
    finally:
        device.close()

if __name__ == "__main__":
    main()
