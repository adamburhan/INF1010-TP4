/****************************************************************************
 * Fichier: PivoterMatrice.h
 * Auteurs: Adam Burhan et Jean-Sébastien Dulong-Grégoire
 * Date: 31 mars 2020
 * Mise a jour : 
 * Description: Déclaratione et implémentation de la classe PivoterMatrice
 ****************************************************************************/

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice() : matrice_(nullptr)
{}


/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}


/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
	Coordonnees newCoords;
	newCoords.x = coords.x - (int)((matrice_->getWidth())/2);
	newCoords.y = coords.y - (int)((matrice_->getHeight())/2);
	return newCoords;
}


/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
	Coordonnees newCoords;
  	newCoords.x = coords.x + (int)((matrice_->getWidth())/2);
  	newCoords.y = coords.y + (int)((matrice_->getHeight())/2);
  	return newCoords;
}


//! Méthode effectuant le pivot de l'objet matrice_ de la classe PivoterMatrice
//! \param direction            Direction dans laquelle la matrice sera pivotée
template <class M>
inline void
PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
	std::unique_ptr<M> newMatrix = matrice_->clone();
	for (size_t i = 0; i < matrice_->getHeight(); i++)
  	{
    	for (size_t j = 0; j < matrice_->getWidth(); j++)
    	{
      		Coordonnees coord;
      		coord.y = static_cast<int>(i);
      		coord.x = static_cast<int>(j);
      		coord = changerCoordonneesCentreMatrice(coord);
      		if (direction == Direction::Right)
      		{
				int temp = coord.y;
        		coord.y = -(coord.x);
				coord.x = temp;
      		}
      		else
      		{
				int temp = coord.x;
        		coord.x = -(coord.y);
				coord.y = temp;
      		}
			coord = recupererCoordonnees(coord);
			matrice_->ajouterElement((*newMatrix)((size_t)coord.y,(size_t)coord.x), i, j);
    	}
  	}
}
#endif
