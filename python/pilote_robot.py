import serial
import time
import os

# Configuration des chemins
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
FICHIER_ACTION = os.path.join(BASE_DIR, "..", "data/action.txt")

# Connexion à l'Arduino
try:
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    time.sleep(2) # Temps pour que l'Arduino reboot
    print("[ROBOT] Connexion Arduino OK")
except:
    print("[ROBOT] Erreur : Arduino non trouvée sur /dev/ttyACM0")
    exit()

def lire_actions():
    if not os.path.exists(FICHIER_ACTION):
        return []
    with open(FICHIER_ACTION, "r", encoding="utf-8") as f:
        return [l.strip() for l in f if l.strip()]

def envoyer_arduino(commande, duree=1):
    print(f"[ROBOT] Envoi : {commande}")
    ser.write(commande.encode())
    time.sleep(duree) # Le robot bouge pendant X secondes
    ser.write(b'S')   # On l'arrête après
    time.sleep(0.1)


def main():
    print("[ROBOT] Lecture des actions en cours...")
    actions = lire_actions()

    if not actions:
        print("[ROBOT] Aucune action à exécuter.")
        return

    for ligne in actions:
        parts = ligne.split()
        action = parts[0]

        if action == "advance":
            envoyer_arduino('1', duree=1.5) # '1' pour avancer
        elif action == "retreat":
            envoyer_arduino('2', duree=1.5) # '2' pour reculer
        elif action == "turn":
            if parts[1] == "left":
                envoyer_arduino('4', duree=0.5) # '4' pour gauche
            else:
                envoyer_arduino('5', duree=0.5) # '5' pour droite
        elif action == "stop":
            envoyer_arduino('3', duree=0.1) # '3' pour stop
            break

    # Nettoyage du fichier action.txt
    open(FICHIER_ACTION, "w").close()
    print("[ROBOT] Toutes les actions ont été effectuées.")

if __name__ == "__main__":
    main()
