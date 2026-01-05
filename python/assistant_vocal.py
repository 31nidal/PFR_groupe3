import speech_recognition as sr
from gtts import gTTS
import sounddevice as sd
import soundfile as sf
import os

r = sr.Recognizer()

# ----- MICRO -----
def record_audio(filename="temp.wav", duration=3, fs=44100):
    print("Speak!")
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype='int16')
    sd.wait()
    sf.write(filename, audio, fs)
    print("End!")
    return filename

# ENVOYER TEXTE AU PROGRAMME C 
def envoyer_texte_au_C(texte):
    with open("../src/commande.txt", "w", encoding="utf-8") as f:
        f.write(texte)

def main():
    # Enregistrement micro
    wav = record_audio()

    # Reconnaissance vocale
    with sr.AudioFile(wav) as source:
        audio = r.record(source)

    try:
        text = r.recognize_google(audio, language="fr-FR")
        print("Vous avez dit :", text)
    except:
        text = ""
        print("Erreur : impossible de reconnaître la parole.")

    # Envoyer au C
    envoyer_texte_au_C(text)

    # Synthèse vocale 
    speech = gTTS("Commande envoyée.", lang="fr")
    speech.save("rep.mp3")
    os.system("afplay rep.mp3")

main()
