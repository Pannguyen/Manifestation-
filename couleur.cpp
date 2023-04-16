#include "couleur.hpp"

const Couleur Couleur::NOIR("noir", "30m");
const Couleur Couleur::ROUGE("rouge", "31m");
const Couleur Couleur::VERT("vert", "32m");
const Couleur Couleur::JAUNE("jaune", "33m");
const Couleur Couleur::BLEU("bleu", "34m");
const Couleur Couleur::MAGENTA("magenta", "35m");
const Couleur Couleur::CYAN("cyan", "36m");
const Couleur Couleur::BLANC("blanc", "37m");

Couleur::Couleur(const std::string &nom, const std::string &code)
    : nom_(nom),
      code_(code)
{
}

Couleur Couleur::creer(const std::string &nom)
{
   if (nom == "noir")
      return NOIR;
   if (nom == "rouge")
      return ROUGE;
   if (nom == "vert")
      return VERT;
   if (nom == "jaune")
      return JAUNE;
   if (nom == "bleu")
      return BLEU;
   if (nom == "magenta")
      return MAGENTA;
   if (nom == "cyan")
      return CYAN;
   if (nom == "blanc")
      return BLANC;
   return BLANC;
}

void Couleur::afficher(std::ostream &os, const std::string &s) const
{
   os << "\033[" + code_ << s << "\033[39m";
}

std::string Couleur::nom() const
{
   return nom_;
}
