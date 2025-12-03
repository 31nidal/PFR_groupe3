import speech_recognition as sr
from gtts import gTTS
import sounddevice as sd
import soundfile as sf
import os

r = sr.Recognizer()

# ----- MICRO (remplace PyAudio) -----
def record_audio(filename="temp.wav", duration=3, fs=44100):
    print("Speak!")
    audio = sd.rec(int(duration * fs), samplerate=fs, channels=1, dtype='int16')
    sd.wait()
    sf.write(filename, audio, fs)
    print("End!")

record_audio()

# ----- RECONNAISSANCE VOCALE -----
with sr.AudioFile("temp.wav") as source:
    audio = r.record(source)

text = r.recognize_google(audio, language="fr-FR")
print("Vous avez dit :", text)

# ----- SYNTHÈSE VOCALE -----
speech = gTTS("je vous ai compris", lang="fr")
speech.save("rep.mp3")
os.system("afplay rep.mp3")
