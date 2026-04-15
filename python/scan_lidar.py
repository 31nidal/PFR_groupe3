import time
from rplidar import RPLidar

PORT_NAME = '/dev/ttyUSB0'

def run():
    lidar = RPLidar(PORT_NAME)
    info = lidar.get_info()
    print(f"Lidar connecté : {info}")

    try:
        lidar.start_motor()
        print('Récupération des distances (Ctrl+C pour stopper)...')
        for scan in lidar.iter_scans():
            for (quality, angle, distance) in scan:
                if distance > 0:
                    print(f"Angle: {angle:3.2f}° | Distance: {distance:4.2f} mm")

    except KeyboardInterrupt:
        print('Arrêt...')

    finally:
        lidar.stop()
        lidar.stop_motor()
        lidar.disconnect()

if __name__ == '__main__':
    run()
