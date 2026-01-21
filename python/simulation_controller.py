from robot import Robot
import time
import turtle

LOIS_FILE = "lois.txt"

def executer_actions_depuis_fichier():
    robot = Robot()

    try:
        with open(LOIS_FILE, "r") as f:
            lignes = f.readlines()
    except FileNotFoundError:
        print("[SIMULATION] Aucun fichier lois.txt")
        return

    print("[SIMULATION] Actions a executer :")
    for l in lignes:
        print("  ->", l.strip())

    for ligne in lignes:
        ligne = ligne.strip()
        if not ligne:
            continue

        # Découpage générique
        parts = ligne.split()

        action = parts[0]

        # ------------------ AVANCER / RECULER ------------------
        if action == "advance":
            if len(parts) >= 3:
                distance = int(parts[1])
            else:
                distance = 50
            robot.avancer(distance)

        elif action == "retreat":
            if len(parts) >= 3:
                distance = int(parts[1])
            else:
                distance = 50
            robot.reculer(distance)

        # ------------------ TOURNER ------------------
        elif action == "turn":
            # formats possibles :
            # turn 90 degrees
            # turn right 90 degrees
            if len(parts) >= 4 and parts[1] in ("left", "right"):
                direction = parts[1]
                angle = int(parts[2])
            elif len(parts) >= 3:
                direction = "right"
                angle = int(parts[1])
            else:
                direction = "right"
                angle = 90

            if direction == "left":
                robot.tourner_gauche(angle)
            else:
                robot.tourner_droite(angle)

        # ------------------ GAUCHE / DROITE SIMPLES ------------------
        elif action == "left":
            robot.tourner_gauche()

        elif action == "right":
            robot.tourner_droite()

        # ------------------ STOP ------------------
        elif action == "stop":
            robot.stop()
            print("[SIMULATION] STOP recu")
            break

        else:
            print(f"[SIMULATION] Action inconnue : {ligne}")

        time.sleep(0.5)  # animation visible

    print("[SIMULATION] Execution terminee")
    turtle.done()  # garde la fenêtre ouverte

if __name__ == "__main__":
    executer_actions_depuis_fichier()
