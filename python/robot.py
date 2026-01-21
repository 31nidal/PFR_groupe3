import turtle
import math

class Robot:

    def __init__(self, start_x=0, start_y=0, initial_heading=0,
                 couleur="blue", vitesse=3):

        # Initialisation de la tortue
        self.t = turtle.Turtle()
        self.t.shape("turtle")
        self.t.speed(vitesse)
        self.t.color(couleur)

        # Position initiale
        self.t.penup()
        self.t.goto(start_x, start_y)
        self.t.setheading(initial_heading)  # 0 = EST, 90 = NORD
        self.t.pendown()

        # Dictionnaire de messages (optionnel, extensible)
        self.messages = {}

    # ================= DEPLACEMENTS =================

    def avancer(self, distance=50):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        action = self.messages.get('avancer', 'avance')
        unite = self.messages.get('unite_distance', 'metres')
        print(f"{prefixe} Robot {action} de {distance} {unite}.")
        self.t.forward(distance)

    def reculer(self, distance=50):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        action = self.messages.get('reculer', 'recule')
        unite = self.messages.get('unite_distance', 'metres')
        print(f"{prefixe} Robot {action} de {distance} {unite}.")
        self.t.backward(distance)

    # ================= ROTATION GENERIQUE =================

    def tourner(self, angle=90, direction="right"):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        action = self.messages.get('tourner', 'tourne')
        unite = self.messages.get('unite_angle', 'degres')

        if direction == "right":
            print(f"{prefixe} Robot {action} de {angle} {unite} a droite.")
            self.t.right(angle)
        elif direction == "left":
            print(f"{prefixe} Robot {action} de {angle} {unite} a gauche.")
            self.t.left(angle)

    # ================= ADAPTATION COMMANDE VOCALE =================

    def tourner_gauche(self, angle=90):
        self.tourner(angle, "left")

    def tourner_droite(self, angle=90):
        self.tourner(angle, "right")

    # ================= AUTRES ACTIONS =================

    def stop(self):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        print(f"{prefixe} Robot arrete.")
        self.t.penup()  # NE FERME PAS la fenêtre

    def start(self):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        print(f"{prefixe} Robot commence a tracer.")
        self.t.pendown()

    def aller_a(self, x, y):
        prefixe = self.messages.get('prefixe', '[TRACE]')
        action = self.messages.get('aller_a', 'se deplace a la position absolue')
        print(f"{prefixe} Robot {action} ({x}, {y}).")
        self.t.penup()
        self.t.goto(x, y)
        self.t.pendown()

    def marquer_cible(self, taille=10, couleur="red"):
        self.t.dot(taille, couleur)

    def ecrire_message(self, message):
        self.t.write(message, align="center",
                     font=("Arial", 10, "normal"))
