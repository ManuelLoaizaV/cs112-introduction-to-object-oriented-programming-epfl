#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique() = delete;
  Brique(Forme, Couleur);
  ostream& afficher(ostream&) const;
};

Brique::Brique(Forme forma, Couleur color)
: forme(forma), couleur(color) {}

ostream& Brique::afficher(ostream& sortie) const {
  if (couleur.size() == 0) sortie << forme;
  else sortie << "(" << forme << ", " << couleur << ")";
  return sortie;
}

ostream& operator<<(ostream& sortie, Brique const& brick) {
  return brick.afficher(sortie);
}

class Construction
{
  friend class Grader;
private:
  vector<vector<vector<Brique>>> contenu;
public:
  Construction(Brique&);
  ostream& afficher(ostream&) const;
  Construction& operator^=(Construction const&);
  Construction& operator-=(Construction const&);
  Construction& operator+=(Construction const&);
};

Construction::Construction(Brique& brick) {
  contenu = {{{brick}}};
}

ostream& Construction::afficher(ostream& sortie) const {
  if (contenu.size() == 0) return sortie;
  int sz_i = contenu.size();
  for (int i = sz_i - 1; i >= 0; i--) {
    sortie << "Couche " << i << " : " << endl;
    int sz_j = contenu[i].size();
    for (int j = sz_j - 1; j >= 0; j--) {
      int sz_k = contenu[i][j].size();
      for (int k = 0; k < sz_k; k++) {
        contenu[i][j][k].afficher(sortie);
      }
      sortie << endl;
    }
  }
  return sortie;
}

ostream& operator<<(ostream& sortie, Construction const& c) {
  return c.afficher(sortie);
}

Construction& Construction::operator^=(Construction const& otro) {
  int sz = otro.contenu.size();
  for (int i = 0; i < sz; i++) contenu.push_back(otro.contenu[i]);
  return *this;
}

const Construction operator^(Construction a, Construction const& b) {
  a ^= b;
  return a;
}

Construction& Construction::operator-=(Construction const& otro) {
  if (otro.contenu.size() >= contenu.size()) {
    int sz = contenu.size();
    for (int i = 0; i < sz; i++) {
      int sz_j = otro.contenu[i].size();
      for (int j = 0; j < sz_j; j++) contenu[i].push_back(otro.contenu[i][j]);
    }
  }
  return *this;
}

const Construction operator-(Construction a, Construction const& b) {
  a -= b;
  return a;
}

Construction& Construction::operator+=(Construction const& otro) {
  int height_a = contenu.size();
  int height_b = otro.contenu.size();
  if (height_b < height_a) return *this;
  int depth_a = contenu[0].size();
  int depth_b = otro.contenu[0].size();
  if (depth_b < depth_a) return *this;
  for (int i = 0; i < height_a; i++) {
    for (int j = 0; j < depth_a; j++) {
      int sz_k = otro.contenu[i][j].size();
      for (int k = 0; k < sz_k; k++) {
        contenu[i][j].push_back(otro.contenu[i][j][k]);
      }
    }
  }
  return *this;
}

const Construction operator+(Construction a, Construction const& b) {
  a += b;
  return a;
}

const Construction operator*(unsigned int n, Construction const& a)
{
  n--;
  Construction ans = a;
  while (n--) ans += a;
  return ans;
}

const Construction operator/(unsigned int n, Construction const& a)
{
  n--;
  Construction ans = a;
  while (n--) ans ^= a;
  return ans;
}

const Construction operator%(unsigned int n, Construction const& a)
{
  n--;
  Construction ans = a;
  while (n--) ans -= a;
  return ans;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
