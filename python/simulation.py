import turtle
import time
import os
from robot import Robot

# ======================================================
# CHEMIN ROBUSTE VERS action.txt (racine du projet)
# ======================================================

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
FICHIER_ACTION = os.path.join(BASE_DIR, "..", "action.txt")

# ======================================================
# PARAMÈTRES D'ANIMATION
# ======================================================

PAS_DISTANCE = 5      # pas de déplacement (pixels)
PAS_ANGLE = 5         # pas de rotation (degrés)
DELAI_ANIM = 0.02     # délai animation

# ======================================================
# LECTURE / ÉCRITURE ACTIONS
# ======================================================

def lire_actions():
    """Lit action.txt ligne par ligne"""
    if not os.path.exists(FICHIER_ACTION):
        return []

    with open(FICHIER_ACTION, "r", encoding="utf-8") as f:
        return [l.strip() for l in f if l.strip()]


def effacer_actions():
    """Vide action.txt après exécution complète"""
    open(FICHIER_ACTION, "w").close()

# ======================================================
# MOUVEMENTS PROGRESSIFS
# ======================================================

def avancer_progressif(robot, distance, sens=1):
    reste = distance
    while reste > 0:
        pas = min(PAS_DISTANCE, reste)
        if sens == 1:
            robot.t.forward(pas)
        else:
            robot.t.backward(pas)
        reste -= pas
        time.sleep(DELAI_ANIM)


def tourner_progressif(robot, angle, direction):
    reste = angle
    while reste > 0:
        pas = min(PAS_ANGLE, reste)
        if direction == "left":
            robot.t.left(pas)
        else:
            robot.t.right(pas)
        reste -= pas
        time.sleep(DELAI_ANIM)

# ======================================================
# APPLICATION D'UNE ACTION
# ======================================================

def appliquer_action(ligne, robot):
    """
    Exécute UNE action normalisée :
    advance X meters
    retreat X meters
    turn left X degrees
    turn right X degrees
    """
    parts = ligne.split()

    if len(parts) < 2:
        print(f"[SIMULATION] Ligne invalide : {ligne}")
        return True

    action = parts[0]

    # ================= AVANCE =================
    if action == "advance":
        distance = int(parts[1])
        print(f"[SIMULATION] Robot avance de {distance} metres")
        avancer_progressif(robot, distance, sens=1)

        # 🔴 POINT ROUGE = FIN D'ACTION
        robot.t.dot(6, "red")

    # ================= RECULE =================
    elif action == "retreat":
        distance = int(parts[1])
        print(f"[SIMULATION] Robot recule de {distance} metres")
        avancer_progressif(robot, distance, sens=-1)

        # 🔴 POINT ROUGE
        robot.t.dot(6, "red")

    # ================= TOURNE =================
    elif action == "turn":
        if len(parts) < 3:
            print(f"[SIMULATION] Action turn invalide : {ligne}")
            return True

        direction = parts[1]
        angle = int(parts[2])

        if direction not in ("left", "right"):
            print(f"[SIMULATION] Direction inconnue : {direction}")
            return True

        print(f"[SIMULATION] Robot tourne {direction} de {angle} degres")
        tourner_progressif(robot, angle, direction)

        # 🔴 POINT ROUGE = FIN DE ROTATION
        robot.t.dot(6, "red")

    # ================= STOP =================
    elif action == "stop":
        print("[SIMULATION] STOP")
        return False

    else:
        print(f"[SIMULATION] Action inconnue : {ligne}")

    return True

# ======================================================
# MAIN (MODE BATCH / FILE D’ACTIONS)
# ======================================================

def main():
    screen = turtle.Screen()
    screen.title("Simulation Robot – PFR (DEBUG VISUEL)")
    screen.bgcolor("white")
    screen.tracer(0)

    robot = Robot()

    print("[SIMULATION] Lecture des actions...")
    actions = lire_actions()

    if not actions:
        print("[SIMULATION] Aucune action a executer.")
        turtle.mainloop()
        return

    for action in actions:
        continuer = appliquer_action(action, robot)
        if not continuer:
            break
        screen.update()

    effacer_actions()
    print("[SIMULATION] Actions terminees, fichier vide.")

    turtle.mainloop()


if __name__ == "__main__":
    main()
