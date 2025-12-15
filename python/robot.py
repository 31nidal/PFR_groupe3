import turtle
import math

class Robot:

	def __init__(self, start_x=0, start_y=0, initial_heading=0, couleur="blue", vitesse=1):

		#initialisation de la tortue
		self.t=turtle.Turtle()
		self.t.shape("turtle")
		self.t.speed(vitesse)
		self.t.color(couleur)

		#position initial
		self.t.penup()
		self.t.goto(start_x, start_y)
		self.t.setheading(initial_heading) # 0=EST, 90=NORT
		self.t.pendown()

	def avancer(self, distance):
		"""Déplace le robot vers l'avant et logue l'action."""
		# AJOUT DE LA TRAÇABILITÉ
		print(f"[TRACE] Robot avance de {distance} metres.")
		self.t.forward(distance)

	def reculer(self, distance):
		"""Déplace le robot vers l'arrière et logue l'action."""
		# AJOUT DE LA TRAÇABILITÉ
		print(f"[TRACE] Robot recule de {distance} metres.")
		self.t.backward(distance)

	def tourner_droite(self, angle):
		print(f"[TRACE] Robot tourne à droite de {angle} degres.")
		self.t.right(angle)

	def tourner_gauche(self, angle):
		print(f"[TRACE] Robot tourne à gauche de {angle} degres.")
		self.t.left(angle)

	def stop(self):
		"""Lève le crayon (mode sans traçage)."""
		print(f"[TRACE] Robot arrête de tracer (penup).")
		self.t.penup()

	def start(self):
		"""Abaisse le crayon (mode traçage)."""
		print(f"[TRACE] Robot commence à tracer (pendown).")
		self.t.pendown()

	def aller_a(self, x, y):
		"""Déplace le robot directement aux coordonnées (x,y)"""
		print(f"[TRACE] Robot se déplace à la position absolue ({x}, {y}).")
		self.t.penup()
		self.t.goto(x, y)
		self.t.pendown()

	def marquer_cible(self, taille=10, couleur="red"):
		"""marque un point pour symboliser une cible ou un obstacle"""
		self.t.dot(taille, couleur)

	def ecrire_message(self, message):
		"""Écrit un message sur l'écran de simulation."""
		self.t.write(message, align="center", font=("Arial", 10, "normal"))

