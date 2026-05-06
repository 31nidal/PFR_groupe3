#!/usr/bin/env python3
"""
lidar_scan.py — Acquisition RPLidar
Usage : python3 lidar_scan.py | python3 lidar_map.py
"""

from rplidar import RPLidar
import time
import sys

PORT = '/dev/ttyUSB0'

print("▶  Connexion au LiDAR...", file=sys.stderr)
lidar = RPLidar(PORT)

try:
    # Attendre que le moteur monte en vitesse
    print("⏳  Démarrage moteur — attente 2 s...", file=sys.stderr)
    lidar.start_motor()
    time.sleep(2)

    print("🔄  Scan en cours (8 s)...", file=sys.stderr)
    start = time.time()

    for scan in lidar.iter_scans():
        for (_, angle, distance) in scan:
            print(f"{angle:.2f} {distance:.2f}")
            sys.stdout.flush()

        if time.time() - start > 8.0:
            break

except KeyboardInterrupt:
    print("\n⚠️  Interrompu par l'utilisateur.", file=sys.stderr)

finally:
    print("⏹  Arrêt du LiDAR...", file=sys.stderr)
    lidar.stop()
    lidar.stop_motor()
    time.sleep(0.5)
    lidar.disconnect()
    print("✅  LiDAR déconnecté.", file=sys.stderr)