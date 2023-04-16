#ifndef COULEUR_HPP
#define COULEUR_HPP

#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// Une couleur possède un nom et un code permettant de changer la couleur
/// du texte dans un terminal.
///
/// @code
/// Couleur coul = Couleur::VERT;
/// coul.afficher(std::cout, "Bonjour !");
/// @endcode
////////////////////////////////////////////////////////////////////////////////
class Couleur {
   public:
      ///@{
      /// Les couleurs disponibles sont des constantes de classe.
      static const Couleur NOIR;
      static const Couleur ROUGE;
      static const Couleur VERT;
      static const Couleur JAUNE;
      static const Couleur BLEU;
      static const Couleur MAGENTA;
      static const Couleur CYAN;
      static const Couleur BLANC;
      ///@}

      /// Affichage en couleur d'une chaîne sur un flot de sortie
      /// @param os un flot de sortie
      /// @param s une chaîne écrite sur le flot
      void afficher(std::ostream &os, const std::string &s) const;

      /// Accesseur
      /// @return le nom de this
      std::string nom() const;

      /// Conversion d'un nom en couleur
      /// @param nom nom d'une couleur dans l'ensemble {noir, rouge, vert, jaune,
      ///        bleu, magenta, cyan, blanc}
      /// @return la couleur qui correspond au nom donné en entrée
      static Couleur creer(const std::string &nom);

   private:
      std::string nom_;  // nom
      std::string code_; // code  sur un terminal

      /// Constructeur utilisé pour créer les constantes statiques
      /// @param nom nom de la couleur
      /// @param code code pour un affichage dans un terminal
      Couleur(const std::string &nom, const std::string &code);
};

#endif
