import speech_recognition as sr
from gtts import gTTS
import sounddevice as sd
import soundfile as sf
import os

# ---------------- CONFIG ----------------
FICHIER_COMMANDE = "../commande.txt"

DUREE_ENREGISTREMENT = 3
FREQUENCE = 44100

# ---------------- INIT ----------------
recognizer = sr.Recognizer()

# ---------------- MICRO ----------------
def record_audio(filename="temp.wav", duration=DUREE_ENREGISTREMENT, fs=FREQUENCE):
    print("Speak!")
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype="int16")
    sd.wait()
    sf.write(filename, audio, fs)
    print("End!")
    return filename

# ---------------- ENVOI AU C ----------------
def envoyer_texte_au_C(texte):
    with open(FICHIER_COMMANDE, "w", encoding="utf-8") as f:
        f.write(texte)

# ---------------- MAIN ----------------
def main():
    wav_file = record_audio()

    with sr.AudioFile(wav_file) as source:
        audio = recognizer.record(source)

    try:
        texte = recognizer.recognize_google(audio, language="fr-FR")
        texte = texte.lower().strip()
        print("Vous avez dit :", texte)
    except sr.UnknownValueError:
        print("Erreur : parole non reconnue")
        texte = ""
    except sr.RequestError:
        print("Erreur : service indisponible")
        texte = ""

    if texte:
        envoyer_texte_au_C(texte)
        speech = gTTS("Commande envoyée.", lang="fr")
        speech.save("rep.mp3")
        os.system("afplay rep.mp3")

# ---------------- EXEC ----------------
if __name__ == "__main__":
    main()
