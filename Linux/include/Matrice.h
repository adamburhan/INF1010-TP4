/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T> class Matrice {

public:
  Matrice();
  // Destructeur
  ~Matrice() = default;
  T operator()(const size_t &posY, const size_t &posX) const;
  // Lecture du fichier
  bool chargerDepuisFichier(const std::string &nomFichier);
  bool lireElement(const std::string &elementFichier, const size_t &posY,
                   const size_t &posX);
  // Remplir un matrice
  bool ajouterElement(const T& element, const size_t &posY, const size_t &posX);
  // Faire une copie
  std::unique_ptr<Matrice<T>> clone() const;
  // Setters
  void setHeight(size_t height);
  void setWidth(size_t width);
  // Getters
  size_t getHeight() const;
  size_t getWidth() const;

private:
  std::vector<std::vector<T>> elements_;
  size_t height_;
  size_t width_;
};

namespace {
static constexpr int CAPACITE_MATRICE = 100U;
}

/**
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice() : elements_(CAPACITE_MATRICE, std::vector<T>(CAPACITE_MATRICE)), height_(0), width_(0)
{
  // elements_.resize(CAPACITE_MATRICE);
	// for (auto& element : elements_)
	// {
	// 	element.resize(CAPACITE_MATRICE);
	// }
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getHeight() const {
  return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getWidth() const {
  return width_;
}

template <typename T> inline T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const 
{
  if (posY > height_ || posX > width_)
  {
    return T();
  }
  return elements_[posY][posX];
}

template <typename T> inline bool Matrice<T>::ajouterElement(const T& element, const size_t &posY, const size_t &posX) 
{

  if (posY <= height_ && posX <= width_)
  {
    elements_[posY][posX] = element;
    return true;
  }
  return false;
}

template <typename T> inline bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX)
{
    T element;
    std::istringstream stream(elementFichier);
    if (stream >> element)
    {
      return ajouterElement(element, posY, posX);
    }
    return true;
}

template <typename T> inline bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) 
{
  	std::ifstream fichier(nomFichier);
  	if (fichier)
  	{
        size_t posY = 0;
  	    size_t posX = 0;
		std::string ligne;
		while (getline(fichier, ligne))
    	{
      		if (ligne.compare("L") == true)
      		{
        		posY++;
        		posX = 0;
      		}
      		else if (lireElement(ligne, posY-1, posX))
      		{
                posX++;
      		}
             else {
                return false;
            }
			height_ = std::max(height_, posY);
			width_ = std::max(width_, posX);
    	}
    	return true;
  	}

    else 
    {
        std::cerr << "Le fichier " << nomFichier
                   << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
         return false;
     }
}

template <typename T> inline std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
	return std::make_unique<Matrice<T>>(*this);
}

template <typename T> inline void Matrice<T>::setHeight(size_t height) 
{
  height_ = (height >= CAPACITE_MATRICE)? CAPACITE_MATRICE : (height <= 0)? 0 : height;
}

template <typename T> inline void Matrice<T>::setWidth(size_t width) 
{
	width_ = (width >= CAPACITE_MATRICE)? CAPACITE_MATRICE : (width <= 0)? 0 : width;
}
#endif
