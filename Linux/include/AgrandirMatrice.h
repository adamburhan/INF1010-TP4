/*
 * Titre : AgrandirMatrice.h - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 Auteur : Nabil Dabouz
 */

#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M> class AgrandirMatrice {
public:
  AgrandirMatrice();
  AgrandirMatrice(M *matrice);
  ~AgrandirMatrice() = default;
  Coordonnees trouverLePlusProcheVoisin(const unsigned int &rapport,
                                        size_t posY, size_t posX) const;
  void redimensionnerImage(const unsigned int &rapport);

private:
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> AgrandirMatrice<M>::AgrandirMatrice() : matrice_(nullptr)
{}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
 * originale
 * @param rapport, le rapport du redimensionnement de l'image
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return coordonnées du point le plus proche
 */
template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int &rapport,
                                              size_t posY, size_t posX) const {
  Coordonnees coordonnee;
  coordonnee.y = static_cast<int>(posY/rapport);
  coordonnee.x = static_cast<int>(posX/rapport);
  return coordonnee;
}

template <class M> void AgrandirMatrice<M>::redimensionnerImage(const unsigned int &rapport)
{
	std::unique_ptr<M> newMatrix = matrice_->clone();
  matrice_->setHeight((matrice_->getHeight()) * rapport);
	matrice_->setWidth(static_cast<size_t>((matrice_->getWidth()) * rapport));
	for (size_t i = 0; i < matrice_->getHeight(); i++)
	{
		for (size_t j = 0; j < matrice_->getWidth(); j++)
		{
			Coordonnees coord = trouverLePlusProcheVoisin(rapport, i, j);
			matrice_->ajouterElement((*newMatrix)(static_cast<size_t>(coord.y), static_cast<size_t>(coord.x)), i, j);
		}
	}
}
#endif
