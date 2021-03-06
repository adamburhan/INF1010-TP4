/****************************************************************************
 * Fichier: Pixel.cpp
 * Auteurs: Adam Burhan et Jean-Sébastien Dulong-Grégoire
 * Date: 31 mars 2020
 * Mise a jour : 
 * Description: Implémentation de la classe Pixel
 ****************************************************************************/
#include "Pixel.h"

//! Constructeur par défaut d'un objet Pixel
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}


/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}



//! Surcharge de l'opérateur =
//! \param pixel              référence constante d'un objet Pixel
void Pixel::operator=(const Pixel &pixel)
{
  bleu_ = pixel.bleu_;
  rouge_ = pixel.rouge_;
  vert_ = pixel.vert_;
}


//! Setter pour l'attribut rouge_ de l'objet Pixel courant
//! \param rouge              Un int représentant le ton de rouge souhaité
void Pixel::setRouge(int rouge)
{
  rouge_ = (rouge >= 255)? 255 : (rouge <= 0)? 0 : static_cast<uint8_t>(rouge);
}


//! Setter pour l'attribut vert_ de l'objet Pixel courant
//! \param vert              Un int représentant le ton de vert souhaité
void Pixel::setVert(int vert)
{
  vert_ = (vert >= 255)? 255 : (vert <= 0)? 0 : static_cast<uint8_t>(vert);
}


//! Setter pour l'attribut bleu_ de l'objet Pixel courant
//! \param bleu              Un int représentant le ton de bleu souhaité
void Pixel::setBleu(int bleu)
{
  bleu_ = (bleu >= 255)? 255 : (bleu <= 0)? 0 : static_cast<uint8_t>(bleu);
}


/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }


/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }


/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }


//! Surcharge de l'opérateur <<
//! \param os              Référence vers un ostream qui sera modifier
//! \param pixel           Pixel passé en paramètre du quel on prend les attributs et les affichons dans le os
//! \return                Une référence vers l'ostream passé en paramètre pour pouvoir l'appelé en casacade
std::ostream &operator<<(std::ostream &os, Pixel pixel)
{
  os << '#' << std::uppercase <<  std::hex << std::setfill('0') << std::setw(2) << (unsigned)pixel.getRouge() << ' ' << std::setw(2) << (unsigned)pixel.getVert()
      << ' ' << std::setw(2) << (unsigned)pixel.getBleu();
  return os;
  /*
  const int TAILLE_TAMPON = 10;
    char tampon[TAILLE_TAMPON];
    sprintf_s(tampon, "#%02X %02X %02X",
              pixel.getRouge(), pixel.getVert(), pixel.getBleu());
    os << tampon;
  */
}
//! Surcharge de l'opérateur <<
//! \param is              Référence vers un istream
//! \param pixel           Référence vers le pixel qui sera modifier par le istream
//! \return                Une référence vers l'istream passé en paramètre pour pouvoir l'appelé en casacade
std::istream &operator>>(std::istream &is, Pixel &pixel)
{
  int rouge;
  int vert;
  int bleu;

  if (is >> rouge >> vert >> bleu)
  {
    pixel.setRouge(rouge);
    pixel.setVert(vert);
    pixel.setBleu(bleu);
  }
  return is;
}