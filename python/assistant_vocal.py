# =======================EN TÊTE=====================================
# FICHIER: assistant_vocal.py
# AUTEUR: YAHYAOUI Nidal
# RÔLE: Implémentation d'un assistant vocal pour capturer les commandes vocales
#       et les écrire dans un fichier texte pour une utilisation ultérieure.
# ===================================================================

import speech_recognition as sr

FICHIER_COMMANDE = "data/commande.txt"

def ecrire_commande(texte):
    with open(FICHIER_COMMANDE, "w", encoding="utf-8") as f:
        f.write(texte + "\n")
import serial
import time

arduino = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

def envoyer_action():
    with open("data/action.txt", "r") as f:
        lines = f.readlines()

    if not lines:
        return

    derniere = lines[-1].strip()
    print("Action envoyée :", derniere)

    if "advance" in derniere:
        arduino.write(b'1')
    elif "retreat" in derniere:
        arduino.write(b'2')
    elif "left" in derniere:
        arduino.write(b'3')
    elif "right" in derniere:
        arduino.write(b'4')
    elif "turn" in derniere:
        arduino.write(b'5')
def main():
    r = sr.Recognizer()

    with sr.Microphone() as source:
        print("Speak!")
        r.adjust_for_ambient_noise(source)
        audio = r.listen(source)

    try:
        # reconnaissance vocale (Google)
        texte = r.recognize_google(audio, language="fr-FR")
        print("Vous avez dit :", texte)
        ecrire_commande(texte)

    except sr.UnknownValueError:
        print("[ERREUR] Je n'ai pas compris")
        ecrire_commande("")

    except sr.RequestError as e:
        print("[ERREUR] Problème API :", e)
        ecrire_commande("")
    envoyer_action()
    print("End!")

if __name__ == "__main__":
    main()