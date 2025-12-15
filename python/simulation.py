import turtle
import random
from robot import Robot # Importez la classe Robot

# 1. Configuration de l'écran (le monde du robot)
def setup_simulation_screen():
	screen = turtle.Screen()
	screen.setup(width=600, height=600)
	screen.title("Simulation de Déplacement Robot (PFR1)")
	return screen

# DÉFINITION DES CAS DE DÉPLACEMENT

def cas_1_ligne_droite(robot: Robot):
	"""Cas 1 : Mouvement simple pour tester 'avancer' et 'tourner'."""
	print("DÉBUT CAS 1 : Ligne droite et rotation ")
	robot.t.color("red")
	robot.avancer(100)
	robot.tourner_droite(90)
	robot.avancer(50)
	robot.ecrire_message("Fin Cas 1")
	robot.aller_a(0, 0) # Retour à l'origine pour le cas suivant
	robot.t.setheading(0)
	print("FIN CAS 1-\n")

def cas_2_parcours_carre(robot: Robot):
	"""Cas 2 : Exécution d'un parcours prédéfini (Carré)."""
	print(" DÉBUT CAS 2 : Parcours Carré ")
	robot.t.color("green")
	robot.t.setheading(90) # Regarder vers le Nord

	for i in range(4):
		robot.avancer(150)
		robot.tourner_droite(90)

	robot.ecrire_message("Parcours Carré effectué")
	robot.aller_a(0, 0)
	robot.t.setheading(0)
	print(" FIN CAS 2 \n")

def cas_3_atteindre_cible(robot: Robot, x_cible=150, y_cible=100):
	"""Cas 3 : Déplacement vers des coordonnées spécifiques (Simulation de la détection)."""
	print(f" DÉBUT CAS 3 : Atteindre la cible à ({x_cible}, {y_cible}) ")
	robot.t.color("violet")

	# Simuler la cible
	robot.t.penup()
	robot.t.goto(x_cible, y_cible)
	robot.marquer_cible(taille=15, couleur="violet")

	# Retourner à la position de départ
	robot.aller_a(0, 0)

	# Déplacement vers la cible
	robot.t.pendown() # On veut tracer le chemin
	robot.aller_a(x_cible, y_cible)

	robot.ecrire_message("Cible atteinte et ramassée!")
	robot.aller_a(0, 0)
	robot.t.setheading(0)
	print(" FIN CAS 3 \n")

def cas_4_gestion_erreur_obstacle(robot: Robot):
	"""Cas 4 : Simule un mouvement avec arrêt et redirection en cas d'obstacle."""
	print(" DÉBUT CAS 4 : Gestion d'obstacle ")

	robot.avancer(150)

	# Simulation de la détection d'un obstacle
	robot.marquer_cible(taille=20, couleur="orange")
	robot.t.color("orange")

	# Action de contournement/redirection
	robot.ecrire_message("ERREUR: Obstacle détecté. Redirection.")
	robot.tourner_gauche(45)
	robot.avancer(50)

	robot.aller_a(0, 0)
	robot.t.setheading(0)
	print(" FIN CAS 4 \n")


#  EXÉCUTION PRINCIPALE
if __name__ == "__main__":
	screen = setup_simulation_screen()

	# Créez une instance du Robot
	mon_robot = Robot(vitesse=2) # Ajustez la vitesse pour l'animation

	# Exécutez les cas de déplacement un par un
	cas_1_ligne_droite(mon_robot)

	# On laisse le temps de voir la fin du cas 1 avant de passer au cas 2
	turtle.time.sleep(1) 

	cas_2_parcours_carre(mon_robot)

	turtle.time.sleep(1)

	cas_3_atteindre_cible(mon_robot, 150, -150)

	turtle.time.sleep(1)

	cas_4_gestion_erreur_obstacle(mon_robot)

	# Assurez-vous que la fenêtre reste ouverte jusqu'à ce que l'utilisateur la ferme
	screen.mainloop()
